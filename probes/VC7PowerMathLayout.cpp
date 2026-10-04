// Actual vendor/SDK math records and independent public ABI/FP dispatch controls.
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <fpieee.h>
#include <float.h>
#include <xmmintrin.h>

extern "C" const unsigned long PowerMathLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(double), sizeof(_exception),
    offsetof(_exception, type), offsetof(_exception, name),
    offsetof(_exception, arg1), offsetof(_exception, arg2), offsetof(_exception, retval),
    sizeof(_FP80), _DOMAIN, _SING, _OVERFLOW, _UNDERFLOW, _TLOSS, _PLOSS,
    _MCW_EM, _EM_INVALID, _EM_ZERODIVIDE, _EM_OVERFLOW, _EM_UNDERFLOW, _EM_INEXACT,
    _MCW_RC, _RC_NEAR, EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_SEARCH
};

extern "C" double PublicPowerControl(double base, double exponent) {
    return pow(base, exponent);
}

extern "C" int PublicMathErrorControl(_exception *record) {
    return _matherr(record);
}

extern "C" void PublicPowerErrorRecordControl(_exception *record, char *name,
                                             double base, double exponent, double result) {
    record->type = _DOMAIN;
    record->name = name;
    record->arg1 = base;
    record->arg2 = exponent;
    record->retval = result;
}

extern "C" int IndependentSseExceptionMaskControl() {
    return (_mm_getcsr() & 0x1f80) == 0x1f80;
}

extern "C" int IndependentX87ExceptionMaskControl() {
    return (_controlfp(0, 0) & _MCW_EM) == _MCW_EM;
}
