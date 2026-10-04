// Complete pinned FILE/SDK declarations and natural ownership/error controls.
#include <stddef.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <errno.h>
#include <internal.h>
#include <file2.h>
#include <msdos.h>

extern "C" const unsigned long StreamFinalizationLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(char), sizeof(wchar_t), sizeof(FILE),
    offsetof(FILE, _ptr), offsetof(FILE, _cnt), offsetof(FILE, _base),
    offsetof(FILE, _flag), offsetof(FILE, _file), offsetof(FILE, _tmpfname),
    _IOREAD, _IOWRT, _IORW, _IOMYBUF, _IOYOURBUF, _IOSETVBUF, _IOERR,
    _IOREAD | _IOWRT | _IORW, _IOMYBUF | _IOYOURBUF,
    static_cast<unsigned long>(~(_IOMYBUF | _IOSETVBUF)),
    static_cast<unsigned short>(~(_IOMYBUF | _IOSETVBUF)),
    static_cast<unsigned long>(~_IOWRT), FILE_ATTRIBUTE_READONLY,
    INVALID_FILE_ATTRIBUTES, EACCES, E_access, static_cast<unsigned long>(EOF)
};

extern "C" void StreamFinalFreeControl(FILE *stream) {
    if (inuse(stream) && mbuf(stream)) {
        free(stream->_base);
        stream->_flag &= ~(_IOMYBUF | _IOSETVBUF);
        stream->_base = stream->_ptr = NULL;
        stream->_cnt = 0;
    }
}

extern "C" int StreamFinalFlushControl(FILE *stream) {
    int result = 0;
    int count;
    if ((stream->_flag & (_IOREAD | _IOWRT)) == _IOWRT && bigbuf(stream)
        && (count = static_cast<int>(stream->_ptr - stream->_base)) > 0) {
        if (_write(stream->_file, stream->_base, count) == count) {
            if (stream->_flag & _IORW)
                stream->_flag &= ~_IOWRT;
        } else {
            stream->_flag |= _IOERR;
            result = EOF;
        }
    }
    stream->_ptr = stream->_base;
    stream->_cnt = 0;
    return result;
}

extern "C" int StreamFinalCloseControl(FILE *stream) {
    int result = EOF;
    if (inuse(stream)) {
        result = _flush(stream);
        _freebuf(stream);
        if (_close(stream->_file) < 0)
            result = EOF;
        else if (stream->_tmpfname != NULL) {
            free(stream->_tmpfname);
            stream->_tmpfname = NULL;
        }
    }
    stream->_flag = 0;
    return result;
}

extern "C" int StreamPathAccessControl(const char *path, int mode) {
    DWORD attributes = GetFileAttributesA(path);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        _dosmaperr(GetLastError());
        return -1;
    }
    if ((attributes & FILE_ATTRIBUTE_READONLY) && (mode & 2)) {
        errno = EACCES;
        _doserrno = E_access;
        return -1;
    }
    return 0;
}

extern "C" int StreamWidePathAccessControl(const wchar_t *path, int mode) {
    DWORD attributes = GetFileAttributesW(path);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        _dosmaperr(GetLastError());
        return -1;
    }
    if ((attributes & FILE_ATTRIBUTE_READONLY) && (mode & 2)) {
        errno = EACCES;
        _doserrno = E_access;
        return -1;
    }
    return 0;
}
