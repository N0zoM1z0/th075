    if ((animationStage)==R1187_FIRST_STAGE && (animationFrame)==0) {
#define R1187_ANGLE_BIAS R1187_ANGLE_BIAS0
#define R1187_UPPER R1187_UPPER0
#define R1187_ANIMATION R1187_ANIMATION0
#include "ReimuRandomShotCommandF1187.inc"
#undef R1187_ANGLE_BIAS
#undef R1187_UPPER
#undef R1187_ANIMATION
    }
    if ((animationStage)==R1187_FIRST_STAGE+1 && (animationFrame)==0) {
#define R1187_ANGLE_BIAS R1187_ANGLE_BIAS1
#define R1187_UPPER R1187_UPPER1
#define R1187_ANIMATION R1187_ANIMATION1
#include "ReimuRandomShotCommandF1187.inc"
#undef R1187_ANGLE_BIAS
#undef R1187_UPPER
#undef R1187_ANIMATION
    }
#if R1187_RESOURCE == 0x4E8
#define R1187_RESOURCE_INPUT inputA
#elif R1187_RESOURCE == 0x4EC
#define R1187_RESOURCE_INPUT inputB
#else
#error Unsupported Reimu random-shot resource field
#endif
    if ((animationStage)==R1187_FIRST_STAGE+2 && (animationFrame)==0 && (scriptCounterF00)<R1187_REPEAT_LIMIT &&
        static_cast<unsigned int>(R1187_RESOURCE_INPUT)>0) {
#define R1187_ANGLE_BIAS R1187_ANGLE_BIAS2
#define R1187_UPPER R1187_UPPER2
#define R1187_ANIMATION R1187_ANIMATION2
#include "ReimuRandomShotCommandF1187.inc"
#undef R1187_ANGLE_BIAS
#undef R1187_UPPER
#undef R1187_ANIMATION
        ++scriptCounterF00;
        ResetSecondaryCounter(R1187_FIRST_STAGE);
    }
#undef R1187_RESOURCE_INPUT
