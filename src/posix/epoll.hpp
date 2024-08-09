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

// Guidance from https://stackoverflow.com/questions/51777259/how-to-code-an-epoll-based-sockets-client-in-c
class epoll : public fd
{
protected:

public:
    void create(int size)
    {
        fd_ = epoll_create(size);
    }

    int ctl(int cmd, int fd, epoll_event* event) const
    {
        return epoll_ctl(fd_, cmd, fd, event);
    }

    int add(epoll_event* event) const
    {
        return ctl(EPOLL_CTL_ADD, event->data.fd, event);
    }

    int wait(epoll_event* events, int max_events, int timeout_ms) const
    {
        return epoll_wait(fd_, events, max_events, timeout_ms);
    }
};

}
