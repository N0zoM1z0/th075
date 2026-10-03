#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <stddef.h>

extern "C" const unsigned long CriticalSectionLayoutProbe[] = {
    sizeof(CRITICAL_SECTION), offsetof(CRITICAL_SECTION, DebugInfo),
    offsetof(CRITICAL_SECTION, LockCount), offsetof(CRITICAL_SECTION, RecursionCount),
    offsetof(CRITICAL_SECTION, OwningThread), offsetof(CRITICAL_SECTION, LockSemaphore),
    offsetof(CRITICAL_SECTION, SpinCount), sizeof(LPCRITICAL_SECTION),
    ERROR_NOT_ENOUGH_MEMORY, STATUS_NO_MEMORY
};
