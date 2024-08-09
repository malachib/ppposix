#pragma once

#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "fwd.h"

namespace posix {

class fd
{
protected:
    int fd_;

public:
    fd() = default;
    constexpr explicit fd(int v) : fd_{v}   {}

    int close() const { return ::close(fd_); }

    // Guidance from
    // https://github.com/millken/c-example/blob/master/epoll-example.c
    // https://stackoverflow.com/questions/71282114/how-to-program-non-blocking-socket-on-connect-and-select
    int flags() const { return ::fcntl(fd_, F_GETFL, 0); }
    int flags(int v) const
    {
        return ::fcntl(fd_, F_GETFL, v);
    }

    operator int() const { return fd_; }

    ///
    /// \brief read - NOTE: Loops, which may not be what you want
    /// \param buf
    /// \param len
    /// \return
    ///
    ssize_t read(void* buf, size_t len) const
    {
        ssize_t bytes_read = 0, bytes_read_total = 0;

        while((bytes_read = ::read(fd_, buf, len)) > 0)
        {
            len -= bytes_read;
            bytes_read_total += bytes_read;
        }

        return bytes_read_total;
    }

    ssize_t write(const void* buf, size_t len) const
    {
        ssize_t bytes_written = 0, total_bytes_written = 0;

        while((bytes_written = ::write(fd_, buf, len)) > 0)
        {
            len -= bytes_written;
            total_bytes_written += bytes_written;
        }

        // NOTE: Possible deviation from standard here
        if(bytes_written < 0)   return -total_bytes_written;

        return total_bytes_written;
    }

    int descriptor() const { return fd_; }
};

}
