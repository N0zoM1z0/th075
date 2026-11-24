#include "GeometryConstants.hpp"
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

namespace GeometryConstants {
const float Six = 6.0f;
const float Eight = 8.0f;
const float Twelve = 12.0f;
const float Fifteen = 15.0f;
const float Sixteen = 16.0f;
const float Nineteen = 19.0f;
const float Twenty = 20.0f;
const float Thirty = 30.0f;
const float Forty = 40.0f;
const float FortyFive = 45.0f;
const float Fifty = 50.0f;
const float Sixty = 60.0f;
const float SixtySix = 66.0f;
const float Seventy = 70.0f;
const float SeventyFive = 75.0f;
const float Eighty = 80.0f;
const float Ninety = 90.0f;
const float NinetyFour = 94.0f;
const float Hundred = 100.0f;
const float HundredFour = 104.0f;
const float HundredTen = 110.0f;
const float HundredFourteen = 114.0f;
const float HundredTwenty = 120.0f;
const float HundredTwentyFive = 125.0f;
const float HundredTwentyEight = 128.0f;
const float HundredThirtyTwo = 132.0f;
const float HundredForty = 140.0f;
const float HundredFifty = 150.0f;
const float HundredSixty = 160.0f;
const float HundredSeventy = 170.0f;
const float HundredEighty = 180.0f;
const float TwoHundred = 200.0f;
const float TwoHundredTwenty = 220.0f;
const float TwoHundredForty = 240.0f;
const float TwoHundredFifty = 250.0f;
const float TwoHundredEighty = 280.0f;
const float ThreeHundredTwenty = 320.0f;
const float DegreesPerTurn = 360.0f;
const float FourHundredTwenty = 420.0f;
const float FourHundredEighty = 480.0f;
const float SixHundredForty = 640.0f;
const float NineHundredSixty = 960.0f;
const float Thousand = 1000.0f;
const float TwelveHundredEighty = 1280.0f;
const float ThirteenHundredEighty = 1380.0f;
const float FourteenHundred = 1400.0f;
const float NegativeTwenty = -20.0f;
const float NegativeHundred = -100.0f;
const float NegativeHundredTwenty = -120.0f;
const float NegativeHundredSixty = -160.0f;
const float RadiansPerDegree = 0.0174532887f;
}
