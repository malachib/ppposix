#pragma once

#include <netdb.h>

namespace posix {

template <class F>
int getaddrinfo (const char* name,
    const char* service,
    const addrinfo* req,
    F&& f)
{
    addrinfo* result;

    int ret = getaddrinfo(name, service, req, &result);

    if(ret != 0)    return ret;

    for(const addrinfo* i = result; i != nullptr; i = i->ai_next)
    {
        f(*i);
    }

    freeaddrinfo(result);

    return 0;
}

}
