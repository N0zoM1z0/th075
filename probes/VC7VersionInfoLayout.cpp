// SDK structure layout controls for the entry's GetVersionExA result fields.
#include <windows.h>
#include <stddef.h>
extern "C" const unsigned long VersionInfoLayoutProbe[6] = {
    sizeof(OSVERSIONINFOA),
    offsetof(OSVERSIONINFOA, dwOSVersionInfoSize),
    offsetof(OSVERSIONINFOA, dwMajorVersion),
    offsetof(OSVERSIONINFOA, dwMinorVersion),
    offsetof(OSVERSIONINFOA, dwBuildNumber),
    offsetof(OSVERSIONINFOA, dwPlatformId)
};
