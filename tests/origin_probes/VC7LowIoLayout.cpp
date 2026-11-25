// Complete vendor handle/thread types and natural 64-bit file offset controls.
#include <stddef.h>
#include <windows.h>
#include <io.h>
#include <errno.h>
#include <internal.h>
#include <mtdll.h>
#include <msdos.h>

union FileOffsetLayoutControl {
    __int64 value;
    struct { unsigned long low; long high; } parts;
};
struct OsErrorLayoutControl { unsigned long oscode; int errnocode; };
extern "C" const unsigned long LowIoLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(long), sizeof(__int64),
    sizeof(ioinfo), offsetof(ioinfo, osfhnd), offsetof(ioinfo, osfile),
    offsetof(ioinfo, pipech), offsetof(ioinfo, lockinitflag), offsetof(ioinfo, lock),
    sizeof(CRITICAL_SECTION), IOINFO_L2E, IOINFO_ARRAY_ELTS, IOINFO_ARRAYS, _NHANDLE_,
    sizeof(ioinfo[IOINFO_ARRAY_ELTS]), sizeof(ioinfo *[IOINFO_ARRAYS]),
    sizeof(_tiddata), offsetof(_tiddata, _terrno), offsetof(_tiddata, _tdoserrno),
    sizeof(FileOffsetLayoutControl), offsetof(FileOffsetLayoutControl, parts.low),
    offsetof(FileOffsetLayoutControl, parts.high), sizeof(OsErrorLayoutControl),
    offsetof(OsErrorLayoutControl, oscode), offsetof(OsErrorLayoutControl, errnocode),
    FOPEN, FEOFLAG, FCRLF, FPIPE, FNOINHERIT, FAPPEND, FDEV, FTEXT,
    EBADF, EINVAL, EACCES, ENOEXEC, EPIPE, ENOSPC, ERROR_INVALID_HANDLE,
    ERROR_WRITE_PROTECT, ERROR_SHARING_BUFFER_EXCEEDED,
    ERROR_INVALID_STARTING_CODESEG, ERROR_INFLOOP_IN_RELOC_CHAIN,
    STD_INPUT_HANDLE, STD_OUTPUT_HANDLE, STD_ERROR_HANDLE
};
extern "C" __int64 FileOffsetIdentityControl(__int64 value) {
    return value;
}
