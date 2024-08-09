#pragma

#include <unistd.h>

namespace posix {

template <size_t N>
int gethostname(char (&name)[N])
{
    return ::gethostname(name, N);
}

}