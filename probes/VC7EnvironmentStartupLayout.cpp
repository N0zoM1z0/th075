// Natural vendor/SDK controls for the complete environment and PE startup graph.
#include <stddef.h>
#include <windows.h>
#include <stdlib.h>
#include <mbctype.h>
#include <mtdll.h>
#include <signal.h>
#include <float.h>
#include <excpt.h>

extern "C" const unsigned long EnvironmentStartupLayoutProbe[] = {
    sizeof(void *), sizeof(wchar_t), MAX_PATH, sizeof(char[MAX_PATH + 1]),
    // The public header leaves _mbctype incomplete; its COMMON definition
    // independently supplies the 257-element bound checked by the verifier.
    sizeof(unsigned char[257]), _M1, CP_ACP, ERROR_CALL_NOT_IMPLEMENTED,
    sizeof(OSVERSIONINFOA), offsetof(OSVERSIONINFOA, dwOSVersionInfoSize),
    offsetof(OSVERSIONINFOA, dwMajorVersion), offsetof(OSVERSIONINFOA, dwMinorVersion),
    offsetof(OSVERSIONINFOA, dwBuildNumber), offsetof(OSVERSIONINFOA, dwPlatformId),
    sizeof(STARTUPINFOA), offsetof(STARTUPINFOA, dwFlags),
    offsetof(STARTUPINFOA, wShowWindow), STARTF_USESHOWWINDOW, SW_SHOWDEFAULT,
    sizeof(IMAGE_DOS_HEADER), offsetof(IMAGE_DOS_HEADER, e_lfanew), IMAGE_DOS_SIGNATURE,
    IMAGE_NT_SIGNATURE, IMAGE_NT_OPTIONAL_HDR32_MAGIC, IMAGE_NT_OPTIONAL_HDR64_MAGIC,
    sizeof(IMAGE_NT_HEADERS32), sizeof(IMAGE_NT_HEADERS64),
    offsetof(IMAGE_NT_HEADERS32, OptionalHeader), offsetof(IMAGE_NT_HEADERS64, OptionalHeader),
    offsetof(IMAGE_NT_HEADERS32, OptionalHeader.NumberOfRvaAndSizes),
    offsetof(IMAGE_NT_HEADERS64, OptionalHeader.NumberOfRvaAndSizes),
    offsetof(IMAGE_NT_HEADERS32, OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress),
    offsetof(IMAGE_NT_HEADERS64, OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress),
    IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR,
    sizeof(_tiddata), offsetof(_tiddata, _pxcptacttab),
    offsetof(_tiddata, _tpxcptinfoptrs), offsetof(_tiddata, _tfpecode),
    sizeof(_XCPT_ACTION), offsetof(_XCPT_ACTION, XcptNum),
    offsetof(_XCPT_ACTION, SigNum), offsetof(_XCPT_ACTION, XcptAction),
    SIGILL, SIGFPE, SIGSEGV, _FPE_INVALID, _FPE_DENORMAL, _FPE_ZERODIVIDE,
    _FPE_OVERFLOW, _FPE_UNDERFLOW, _FPE_INEXACT, _FPE_STACKOVERFLOW,
    EXCEPTION_CONTINUE_EXECUTION, EXCEPTION_CONTINUE_SEARCH, EXCEPTION_EXECUTE_HANDLER
};
