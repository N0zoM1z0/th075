#include "FloatConstants.hpp"
#include "MathFloatHelpers.hpp"
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

namespace FloatConstants {
const float Zero = 0.0f;
const float OneHundredth = 0.01f;
const float OneTenth = 0.1f;
const float OneFifth = 0.2f;
const float Quarter = 0.25f;
const float ThreeTenths = 0.3f;
const float Half = 0.5f;
const float ThreeFifths = 0.6f;
const float ThreeQuarters = 0.75f;
const float FourFifths = 0.8f;
const float One = 1.0f;
const float OneAndHalf = 1.5f;
const float Two = 2.0f;
const float Three = 3.0f;
const float Four = 4.0f;
const float Five = 5.0f;
const float Ten = 10.0f;
const double HalfDouble = 0.5;
const double ThreeQuartersDouble = 0.75;
}
