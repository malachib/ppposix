#pragma once

#include <cassert>

#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "fd.hpp"

namespace posix {

class socket : public fd
{
public:
    socket() = default;

    constexpr explicit socket(int v) : fd{v} {}

    template <class T>
    int recv(T* v, int flags) const
    {
        return ::recv(fd_, v, sizeof(T), flags);
    }

    int recv(void* buffer, size_t length, int flags,
             struct sockaddr* addr,
             socklen_t* addr_len) const
    {
        return ::recvfrom(fd_, buffer, length, flags, addr, addr_len);
    }

    template <class T>
    int recv(T* buffer, int flags,
             struct sockaddr* addr,
             socklen_t* addr_len) const
    {
        return ::recvfrom(fd_, buffer, sizeof(T), flags, addr, addr_len);
    }

    ///
    /// \brief send NOTE: This guy auto loops, which may not always be what you want
    /// \param buffer
    /// \param sz
    /// \param flags
    /// \return
    ///
    ssize_t send(const void* buffer, size_t sz, int flags) const
    {
        ssize_t sent = 0, sent_total = 0;

        while(sz > 0 && (sent = ::send(fd_, buffer, sz, flags)) > 0)
        {
            sz -= sent;
            sent_total += sent;
        }

        return sent_total;
    }

    template <class T>
    ssize_t send(const T* buffer, int flags) const
    {
        return send(buffer, sizeof(T), flags);
    }

    // Guidance from
    // https://stackoverflow.com/questions/3217650/how-can-i-find-the-socket-type-from-the-socket-descriptor
    int type() const
    {
        int v;
        socklen_t l = sizeof(v);

        int ret = getsockopt(fd_, SOL_SOCKET, SO_TYPE, &v, &l);

        assert(ret == 0);

        return v;
    }

    template <class T>
    int setopt(int level, int option_name, const T* v) const
    {
        return setsockopt(fd_, level, option_name, v, socklen_t(sizeof(v)));
    }

    int descriptor() const { return fd_; }
};

}
