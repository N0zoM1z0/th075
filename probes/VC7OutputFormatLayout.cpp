// Complete vendor types, with natural va_list and indirect conversion controls.
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <locale.h>
#include <file2.h>
#include <fltintrn.h>
#include <errno.h>

struct CountedStringLayoutControl {
    short length;
    short maximum_length;
    char *buffer;
};
extern "C" const unsigned long OutputFormatLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(long), sizeof(short), sizeof(char),
    sizeof(wchar_t), sizeof(double), sizeof(long double), sizeof(va_list), sizeof(__int64),
    sizeof(FILE), offsetof(FILE, _ptr), offsetof(FILE, _cnt), offsetof(FILE, _base),
    offsetof(FILE, _flag), offsetof(FILE, _file), offsetof(FILE, _charbuf),
    offsetof(FILE, _bufsiz), offsetof(FILE, _tmpfname), _IOWRT | _IOSTRG, INT_MAX,
    sizeof(DOUBLE), sizeof(LONGDOUBLE), sizeof(PFV[6]), sizeof(PF0), sizeof(PF1), sizeof(PF3),
    sizeof(CountedStringLayoutControl), offsetof(CountedStringLayoutControl, length),
    offsetof(CountedStringLayoutControl, maximum_length), offsetof(CountedStringLayoutControl, buffer),
    sizeof(unsigned short[257]), sizeof(char[512]), EILSEQ
};
extern "C" unsigned __int64 FormatVa64Control(int marker, ...) {
    va_list arguments;
    va_start(arguments, marker);
    unsigned __int64 value = va_arg(arguments, unsigned __int64);
    va_end(arguments);
    return value;
}
extern "C" void FormatFloatCallControl(PF0 conversion, DOUBLE *value, char *buffer) {
    conversion(value, buffer, 'g', 6, 0);
}
