#pragma once
#include <stddef.h>

// The Japanese original TH075 has three adjacent 32-bit fields at
// background stage receiver+0x0C/+0x10/+0x14. Two true original
// initialization grammars exist: 30 constructors zero integer words,
// while 6 constructors write floats 640.0f/100.0f/100.0f.
// Both are BORROWED offset-local views, not instantiable stage owners.
// Names describe source representation, not original historical classes.
struct BackgroundStageZeroFieldsF933 {
    unsigned int zeroAt0C;
    unsigned int zeroAt10;
    unsigned int zeroAt14;
};
struct BackgroundStageFloatFieldsF933 {
    float floatAt0C;
    float floatAt10;
    float floatAt14;
};
typedef char BackgroundStageZeroSizeF933[
    sizeof(BackgroundStageZeroFieldsF933)==12 ? 1 : -1];
typedef char BackgroundStageFloatSizeF933[
    sizeof(BackgroundStageFloatFieldsF933)==12 ? 1 : -1];
typedef char BackgroundStageFieldOffsetsF933[
    offsetof(BackgroundStageZeroFieldsF933,zeroAt10)==4 &&
    offsetof(BackgroundStageZeroFieldsF933,zeroAt14)==8 &&
    offsetof(BackgroundStageFloatFieldsF933,floatAt10)==4 &&
    offsetof(BackgroundStageFloatFieldsF933,floatAt14)==8 ? 1 : -1];
