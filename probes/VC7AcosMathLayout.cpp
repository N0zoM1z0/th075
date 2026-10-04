// Complete actual SDK math records and independent public acos/range controls.
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <fpieee.h>
#include <float.h>

extern "C" const unsigned long AcosMathLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(double), sizeof(_exception),
    offsetof(_exception, type), offsetof(_exception, name),
    offsetof(_exception, arg1), offsetof(_exception, arg2), offsetof(_exception, retval),
    sizeof(_FP80), _DOMAIN, _SING, _OVERFLOW, _UNDERFLOW, _TLOSS, _PLOSS,
    _MCW_EM, _EM_INVALID, _MCW_RC, _RC_NEAR,
    EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_SEARCH
};

extern "C" double PublicAcosControl(double argument) {
    return acos(argument);
}

extern "C" int PublicAcosMathErrorControl(_exception *record) {
    return _matherr(record);
}

extern "C" int IndependentAcosRangeControl(double argument) {
    return argument < -1.0 || argument > 1.0;
}

extern "C" int IndependentAcosNanControl(double argument) {
    return argument != argument;
}

extern "C" unsigned int PublicAcosControlWordControl() {
    return _controlfp(0, 0);
}
