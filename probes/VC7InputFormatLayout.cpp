// Complete vendor types and natural input argument/conversion controls.
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <fltintrn.h>

extern "C" const unsigned long InputFormatLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(long), sizeof(short), sizeof(char),
    sizeof(wchar_t), sizeof(va_list), sizeof(__int64), sizeof(FILE),
    offsetof(FILE, _ptr), offsetof(FILE, _cnt), offsetof(FILE, _base),
    offsetof(FILE, _flag), offsetof(FILE, _file), offsetof(FILE, _charbuf),
    offsetof(FILE, _bufsiz), offsetof(FILE, _tmpfname),
    _IOREAD | _IOSTRG | _IOMYBUF, (unsigned long)EOF,
    sizeof(unsigned char[256 / CHAR_BIT]), CHAR_BIT, _SPACE, _HEX, _LEADBYTE,
    sizeof(float), sizeof(double), sizeof(long double), sizeof(PF2),
    sizeof(PFV[6]), sizeof(DOUBLE), sizeof(LONGDOUBLE), EILSEQ,
    _CVTBUFSIZE, sizeof(char[_CVTBUFSIZE + 1])
};

extern "C" int *InputArgumentPointerControl(const char *source, const char *format, ...) {
    va_list arguments;
    va_start(arguments, format);
    int *destination = va_arg(arguments, int *);
    va_end(arguments);
    return destination;
}

extern "C" unsigned __int64 InputInt64MultiplyControl(unsigned __int64 left,
                                                     unsigned __int64 right) {
    return left * right;
}

extern "C" void InputFloatAssignControl(PF2 assign, char *destination, char *text) {
    assign(1, destination, text);
}
