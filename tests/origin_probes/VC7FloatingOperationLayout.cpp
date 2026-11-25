// Pinned SDK/CRT types and natural ABI models for complete floating owners.
#include <stddef.h>
#include <math.h>
#include <float.h>
#include <fpieee.h>

// Storage observed between EBP-16 and the cookie at EBP-4 in both wrappers.
// This models the buffer width, without naming its unavailable private typedef.
enum { FloatingParserStorageControl = 12 };

extern "C" const unsigned long FloatingOperationLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(double), sizeof(long double), sizeof(_FP80),
    sizeof(((_FP80 *)0)->W), sizeof(struct _exception),
    offsetof(struct _exception, type), offsetof(struct _exception, name),
    offsetof(struct _exception, arg1), offsetof(struct _exception, arg2),
    offsetof(struct _exception, retval), FloatingParserStorageControl,
    sizeof(char **), _MCW_RC, _RC_NEAR, _RC_DOWN, _RC_UP, _RC_CHOP,
    _MCW_PC, _PC_53, _PC_64, _SW_INVALID, _SW_ZERODIVIDE,
    _SW_OVERFLOW, _SW_UNDERFLOW, _SW_INEXACT
};

extern "C" double FloatingUnaryCallControl(double (*worker)(double), double value) {
    return worker(value);
}
extern "C" double FloatingBinaryCallControl(double (*worker)(double, double),
                                              double value, double toward) {
    return worker(value, toward);
}
extern "C" double FloatingScaleCallControl(double (*worker)(double, int),
                                             double value, int exponent) {
    return worker(value, exponent);
}
extern "C" int FloatingOutputCallControl(int (*worker)(_FP80 *, const char *),
                                           _FP80 *output, const char *text) {
    return worker(output, text);
}
extern "C" int FloatingParseConvertControl(
    int (*parser)(unsigned char *, char **, const char *, int, int, int, int),
    int (*converter)(const unsigned char *, _FP80 *),
    _FP80 *output, char **end, const char *text, int flag) {
    unsigned char storage[FloatingParserStorageControl];
    int result = parser(storage, end, text, flag, 0, 0, 0);
    if (converter(storage, output) == 1)
        result |= 2;
    return result;
}
