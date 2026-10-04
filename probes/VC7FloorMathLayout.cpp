// Complete SDK records and independent public rounded-math/rounding controls.
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <fpieee.h>
#include <float.h>
#include <xmmintrin.h>

extern "C" const unsigned long FloorMathLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(double), sizeof(_exception),
    offsetof(_exception, type), offsetof(_exception, name),
    offsetof(_exception, arg1), offsetof(_exception, arg2), offsetof(_exception, retval),
    sizeof(_FP80), _DOMAIN, _MCW_EM, _EM_INVALID, _MCW_RC,
    _RC_NEAR, _RC_DOWN, _RC_UP, _RC_CHOP, _FPCLASS_NZ,
    EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_SEARCH
};

extern "C" double PublicFloorControl(double value) {
    return floor(value);
}

extern "C" void PublicFloorCeilPairControl(double value, double *lower, double *upper) {
    *lower = floor(value);
    *upper = ceil(value);
}

extern "C" double PublicModfControl(double value, double *integer) {
    return modf(value, integer);
}

extern "C" int PublicNegativeZeroClassControl(double value) {
    return _fpclass(value) == _FPCLASS_NZ;
}

extern "C" int IndependentFloorSseMaskControl() {
    return (_mm_getcsr() & 0x1f80) == 0x1f80;
}

extern "C" unsigned int PublicDownwardRoundingControl() {
    return _controlfp(_RC_DOWN, _MCW_RC);
}
