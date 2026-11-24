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
const float OneThousandth = 0.001f;
const float OneFourHundredth = 0.0025f;
const float OneTwoHundredth = 0.005f;
const float TwoHundredths = 0.02f;
const float OneFortieth = 0.025f;
const float ThreeHundredths = 0.03f;
const float FourHundredths = 0.04f;
const float OneTwentieth = 0.05f;
const float SevenHundredths = 0.07f;
const float EightHundredths = 0.08f;
const float FifteenHundredths = 0.15f;
const float NineteenHundredths = 0.19f;
const float TwoFifths = 0.4f;
const float FortyFiveHundredths = 0.45f;
const float SixtyFiveHundredths = 0.65f;
const float EightyFiveHundredths = 0.85f;
const float NineTenths = 0.9f;
const float NinetyFourHundredths = 0.94f;
const float NinetyFiveHundredths = 0.95f;
const float NinetySevenHundredths = 0.97f;
const float NinetyEightHundredths = 0.98f;
const float OneAndOneTenth = 1.1f;
const float OneAndSevenTenths = 1.7f;
const float TwoAndHalf = 2.5f;
const double OneHundredthDouble = 0.01;
const double ThreeHundredthsDouble = 0.03;
const double OneTwentiethDouble = 0.05;
const double OneTenthDouble = 0.1;
const double QuarterDouble = 0.25;
const double FourFifthsDouble = 0.8;
const double EightyFiveHundredthsDouble = 0.85;
const double OneDouble = 1.0;
const double OneAndHalfDouble = 1.5;
const double NineHundredNinetyEightAndNineTenths = 998.9;
const float SuikaMinimumScale = 0.333f;
const float SevenTenths = 0.7f;
const float FiftyFiveHundredths = 0.55f;
const float TenAndHalf = 10.5f;
const float TwentyTwoAndHalf = 22.5f;
const float FourAndHalf = 4.5f;
const float NegativeFourAndHalf = -4.5f;
const float OneAndThreeTenths = 1.3f;
const float ThirtyFiveHundredths = 0.35f;
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
const float NegativeTwo = -2.0f;
const float NegativeSix = -6.0f;
const float NegativeSixty = -60.0f;
const float NegativeHundredEighty = -180.0f;
const float NegativeTwoHundred = -200.0f;
const float NegativeTwoHundredForty = -240.0f;
const float NegativeThreeHundred = -300.0f;
const float NegativeThreeHundredTwenty = -320.0f;
const float NegativeFourHundred = -400.0f;
const float NegativeFourHundredEighty = -480.0f;
const float NegativeFiveHundredForty = -540.0f;
const float Seven = 7.0f;
const float Eleven = 11.0f;
const float ThirtyFive = 35.0f;
const float SixtyFour = 64.0f;
const float SixtyFive = 65.0f;
const float SixtySeven = 67.0f;
const float EightyThree = 83.0f;
const float EightySix = 86.0f;
const float HundredSeven = 107.0f;
const float HundredThirtyFive = 135.0f;
const float HundredThirtySix = 136.0f;
const float HundredFortyFive = 145.0f;
const float TwoHundredFiftyFive = 255.0f;
const float TwoHundredFiftySix = 256.0f;
const float FourHundred = 400.0f;
const float FiveHundredForty = 540.0f;
const float NineHundred = 900.0f;
const float ThousandTwentyFour = 1024.0f;
const float ElevenHundredEighty = 1180.0f;
const float FourteenHundredEighty = 1480.0f;
const float FifteenHundredEighty = 1580.0f;
const float SixteenHundred = 1600.0f;
const float TwoThousand = 2000.0f;
const float TenThousand = 10000.0f;
const float ThreeHundred = 300.0f;
const float Nine = 9.0f;
const float NineHundredTwenty = 920.0f;
const float NegativeFive = -5.0f;
const float TwentyFive = 25.0f;
const float FiveHundredFifty = 550.0f;
const float SevenHundredFifty = 750.0f;
const float HundredFortyFour = 144.0f;
const float HundredThirty = 130.0f;
const float NinetySix = 96.0f;
const float NegativeFifteen = -15.0f;
const float NegativeTen = -10.0f;
const float NegativeOne = -1.0f;
const float EightyFive = 85.0f;
const float NinetyFive = 95.0f;
const float HundredFifteen = 115.0f;
const float HundredSixteen = 116.0f;
const float ThirtySix = 36.0f;
const float FortyOne = 41.0f;
const float NegativeEighty = -80.0f;
const float SeventySeven = 77.0f;
const float HundredThirtyOne = 131.0f;
const float HundredNinety = 190.0f;
const float Eighteen = 18.0f;
const float HundredSeventySeven = 177.0f;
const float HundredFive = 105.0f;
const float HundredEighteen = 118.0f;
const float TwentyFour = 24.0f;
const float SeventyTwo = 72.0f;
const float ThreeHundredEighty = 380.0f;
const float NegativeTwentyFive = -25.0f;
const float EightySeven = 87.0f;
const float HundredTwelve = 112.0f;
const float HundredSix = 106.0f;
const float EightHundred = 800.0f;
const float HundredThirtySeven = 137.0f;
const float HundredSixtyEight = 168.0f;
}
