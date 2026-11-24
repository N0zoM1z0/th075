#include <math.h>

// Shared game-side floating-point wrappers used by fighter/object policy.
// The x86 float overloads in the pinned VC7.1 math.h remain inline workers;
// these wrappers are separate original game call targets.
float __cdecl AngleAt00483300(float y, float x)
{
    return atan2f(y, x);
}

float __cdecl AbsFloatAt00412D90(float value)
{
    return fabsf(value);
}

float __cdecl MagnitudeAt00428D20(float value)
{
    return sqrtf(value);
}

float __cdecl CameraCosineAt0040D900(float radians)
{
    return cosf(radians);
}

float __cdecl CameraSineAt0040D940(float radians)
{
    return sinf(radians);
}
