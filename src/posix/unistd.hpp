#pragma

#include <unistd.h>

namespace posix {

// DEBT: Ah, looks like posix namespace is somewhat reserved
// However, in 2016 it was not used yet https://stackoverflow.com/questions/36374481/is-the-posix-namespace-used
template <size_t N>
int gethostname(char (&name)[N])
{
    return ::gethostname(name, N);
}

}