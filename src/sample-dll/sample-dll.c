
#include "common.h"


INT DoSomething()
{
    return MessageBoxA(NULL, "Hello, world!", "sample-dll", MB_OK | MB_ICONINFORMATION);
}