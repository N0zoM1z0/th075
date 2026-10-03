// Complete vendor FP carrier sizes and control masks, with no game declarations.
#include <stddef.h>
#include <float.h>
#include <fltintrn.h>
extern "C" const unsigned long FloatingPointLayoutProbe[] = {
    sizeof(DOUBLE), sizeof(LONGDOUBLE), sizeof(long double), sizeof(PFV[6]),
    sizeof(PF0), sizeof(PF1), sizeof(PF2), sizeof(PF3), sizeof(PF4), sizeof(PF5),
    sizeof(_strflt), offsetof(_strflt, sign), offsetof(_strflt, decpt),
    offsetof(_strflt, flag), offsetof(_strflt, mantissa),
    _MCW_EM, _EM_INEXACT, _EM_UNDERFLOW, _EM_OVERFLOW, _EM_ZERODIVIDE,
    _EM_INVALID, _EM_DENORMAL, _MCW_RC, _RC_NEAR, _RC_DOWN, _RC_UP, _RC_CHOP,
    _MCW_PC, _PC_64, _PC_53, _PC_24, _MCW_IC, _IC_AFFINE, _IC_PROJECTIVE,
    _CW_DEFAULT, sizeof(void *)
};
