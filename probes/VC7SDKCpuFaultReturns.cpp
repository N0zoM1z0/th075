#include <d3dx8.h>
#include <stddef.h>

extern void ObserveCpuInstruction();

DWORD RetainFlagOnFault(DWORD savedFlag)
{
    try {
        ObserveCpuInstruction();
    } catch (...) {
        return savedFlag;
    }
    return savedFlag | 4;
}

DWORD ClearFlagOnFault()
{
    try {
        ObserveCpuInstruction();
    } catch (...) {
        return 0;
    }
    return 4;
}

extern "C" const unsigned long SDKCpuFeatureLayout[] = {
    sizeof(DWORD),
    PF_XMMI_INSTRUCTIONS_AVAILABLE,
    PF_3DNOW_INSTRUCTIONS_AVAILABLE,
    PF_XMMI64_INSTRUCTIONS_AVAILABLE,
    sizeof(OSVERSIONINFOA),
    offsetof(OSVERSIONINFOA, dwMajorVersion),
    offsetof(OSVERSIONINFOA, dwMinorVersion),
    offsetof(OSVERSIONINFOA, dwBuildNumber),
    offsetof(OSVERSIONINFOA, dwPlatformId)
};
