// Natural vendor/SDK layouts for complete initializer, IO and signal evidence.
#include <stddef.h>
#include <windows.h>
#include <stdio.h>
#include <internal.h>
#include <mtdll.h>
#include <msdos.h>
#include <file2.h>
#include <signal.h>
#include <excpt.h>
#include <float.h>

extern "C" const unsigned long InitializerLayoutProbe[] = {
    sizeof(ioinfo), offsetof(ioinfo, osfhnd), offsetof(ioinfo, osfile),
    offsetof(ioinfo, pipech), offsetof(ioinfo, lockinitflag), offsetof(ioinfo, lock),
    sizeof(CRITICAL_SECTION), IOINFO_L2E, IOINFO_ARRAY_ELTS, IOINFO_ARRAYS, _NHANDLE_,
    sizeof(ioinfo[IOINFO_ARRAY_ELTS]), sizeof(ioinfo *[IOINFO_ARRAYS]),
    sizeof(FILE), offsetof(FILE, _ptr), offsetof(FILE, _cnt), offsetof(FILE, _base),
    offsetof(FILE, _flag), offsetof(FILE, _file), offsetof(FILE, _charbuf),
    offsetof(FILE, _bufsiz), offsetof(FILE, _tmpfname),
    _IOB_ENTRIES, sizeof(FILE[_IOB_ENTRIES]), _NSTREAM_, _INTERNAL_BUFSIZ,
    FOPEN, FPIPE, FDEV, FTEXT, _IOREAD, _IOWRT, _IOYOURBUF,
    sizeof(STARTUPINFOA), offsetof(STARTUPINFOA, cbReserved2), offsetof(STARTUPINFOA, lpReserved2),
    STD_INPUT_HANDLE, STD_OUTPUT_HANDLE, STD_ERROR_HANDLE, FILE_TYPE_CHAR, FILE_TYPE_PIPE,
    sizeof(_tiddata), offsetof(_tiddata, _terminate), offsetof(_tiddata, _pxcptacttab),
    offsetof(_tiddata, _tpxcptinfoptrs), offsetof(_tiddata, _tfpecode),
    sizeof(_XCPT_ACTION), offsetof(_XCPT_ACTION, XcptNum),
    offsetof(_XCPT_ACTION, SigNum), offsetof(_XCPT_ACTION, XcptAction),
    SIGINT, SIGILL, SIGFPE, SIGSEGV, SIGTERM, SIGBREAK, SIGABRT, _FPE_EXPLICITGEN, _SIGNAL_LOCK,
    sizeof(EXCEPTION_RECORD), offsetof(EXCEPTION_RECORD, ExceptionCode),
    offsetof(EXCEPTION_RECORD, NumberParameters), offsetof(EXCEPTION_RECORD, ExceptionInformation),
    sizeof(((EXCEPTION_RECORD *)0)->ExceptionInformation) / sizeof(ULONG_PTR), sizeof(EXCEPTION_POINTERS),
    offsetof(EXCEPTION_POINTERS, ExceptionRecord), offsetof(EXCEPTION_POINTERS, ContextRecord),
    EXCEPTION_CONTINUE_EXECUTION, EXCEPTION_CONTINUE_SEARCH, EXCEPTION_EXECUTE_HANDLER,
    sizeof(LPTOP_LEVEL_EXCEPTION_FILTER), sizeof(HANDLE), sizeof(void *)
};
