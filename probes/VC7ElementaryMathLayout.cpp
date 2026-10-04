// Complete vendor math records and operation codes, emitted naturally by VC7.
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <fpieee.h>

extern "C" const unsigned long ElementaryMathLayoutProbe[] = {
    sizeof(void *), sizeof(double), sizeof(_FP80), sizeof(_exception),
    offsetof(_exception, type), offsetof(_exception, arg1),
    offsetof(_exception, arg2), offsetof(_exception, retval),
    _DOMAIN, _FpCodeCos, _FpCodeSin, _FpCodeSquareRoot
};
