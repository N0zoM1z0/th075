// Complete vendor/SDK exception layouts and natural bitfield controls.
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <float.h>
#include <fpieee.h>

extern "C" const unsigned long FPDispatchLayoutProbe[] = {
    sizeof(void *), sizeof(double), sizeof(_FP80), sizeof(_FP128),
    sizeof(_FPIEEE_VALUE), sizeof(_FPIEEE_EXCEPTION_FLAGS), sizeof(_FPIEEE_RECORD),
    offsetof(_FPIEEE_RECORD, Cause), offsetof(_FPIEEE_RECORD, Enable),
    offsetof(_FPIEEE_RECORD, Status), offsetof(_FPIEEE_RECORD, Operand1),
    offsetof(_FPIEEE_RECORD, Operand2), offsetof(_FPIEEE_RECORD, Result),
    sizeof(_exception), offsetof(_exception, type), offsetof(_exception, name),
    offsetof(_exception, arg1), offsetof(_exception, arg2), offsetof(_exception, retval),
    _DOMAIN, _SING, _OVERFLOW, _UNDERFLOW, _TLOSS, _PLOSS,
    _FpFormatFp64, _FpCodeSquareRoot, _FpCodeAtan2,
    _FpRoundNearest, _FpRoundMinusInfinity, _FpRoundPlusInfinity, _FpRoundChopped,
    _FpPrecisionFull, _FpPrecision53, _FpPrecision24,
    _EM_INVALID, _EM_DENORMAL, _EM_ZERODIVIDE, _EM_OVERFLOW, _EM_UNDERFLOW, _EM_INEXACT,
    _MCW_RC, _MCW_PC, _CW_DEFAULT,
    STATUS_FLOAT_INVALID_OPERATION, STATUS_FLOAT_DIVIDE_BY_ZERO,
    STATUS_FLOAT_OVERFLOW, STATUS_FLOAT_UNDERFLOW, STATUS_FLOAT_INEXACT_RESULT
};

extern "C" const _FPIEEE_EXCEPTION_FLAGS FPDispatchFlagsProbe = {1, 1, 1, 1, 1};
extern "C" const _FPIEEE_VALUE FPDispatchValueProbe = {{0}, 1, _FpFormatFp64};
extern "C" const _FPIEEE_RECORD FPDispatchRecordProbe = {
    _FpRoundNearest, _FpPrecision53, _FpCodeAtan2, {0}, {0}, {0},
    {{0}, 0, _FpFormatFp64}, {{0}, 0, _FpFormatFp64}, {{0}, 0, _FpFormatFp64}
};
