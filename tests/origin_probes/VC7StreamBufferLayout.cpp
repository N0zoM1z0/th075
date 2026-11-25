// Complete vendor FILE/handle layouts and natural narrow-byte/cdecl controls.
#include <stddef.h>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <internal.h>
#include <file2.h>
#include <msdos.h>
#include <mtdll.h>

extern "C" const unsigned long StreamBufferLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(long), sizeof(char), sizeof(wchar_t),
    sizeof(FILE), offsetof(FILE, _ptr), offsetof(FILE, _cnt), offsetof(FILE, _base),
    offsetof(FILE, _flag), offsetof(FILE, _file), offsetof(FILE, _charbuf),
    offsetof(FILE, _bufsiz), offsetof(FILE, _tmpfname),
    _IOB_ENTRIES, sizeof(FILE[_IOB_ENTRIES]), _INTERNAL_BUFSIZ, _SMALL_BUFSIZ,
    _IOREAD, _IOWRT, _IONBF, _IOMYBUF, _IOEOF, _IOERR, _IOSTRG, _IORW,
    _IOYOURBUF, _IOSETVBUF, _IOCTRLZ, FOPEN, FEOFLAG, FAPPEND, FDEV, FTEXT,
    sizeof(ioinfo), offsetof(ioinfo, osfhnd), offsetof(ioinfo, osfile),
    offsetof(ioinfo, pipech), offsetof(ioinfo, lockinitflag), offsetof(ioinfo, lock),
    sizeof(CRITICAL_SECTION), IOINFO_L2E, IOINFO_ARRAY_ELTS, IOINFO_ARRAYS, _NHANDLE_,
    sizeof(ioinfo *[IOINFO_ARRAYS]), sizeof(_tiddata),
    offsetof(_tiddata, _terrno), offsetof(_tiddata, _tdoserrno),
    EOF, SEEK_END, sizeof(((FILE *)0)->_charbuf), sizeof(char[_INTERNAL_BUFSIZ])
};
extern "C" int StreamByteLoadControl(FILE *stream) {
    return (unsigned char)*stream->_ptr;
}
extern "C" int StreamPushbackCallControl(int character, FILE *stream) {
    return _ungetc_lk(character, stream);
}
