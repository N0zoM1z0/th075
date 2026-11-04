#pragma once
#include <stddef.h>

// Nine physically adjacent actor +0x1C..+0x3F transform floats observed
// in the original complete FighterRender function. Borrowed only; this is
// neither an allocated object nor a claim about the full fighter owner.
struct FighterRenderTransformWindowF1094 {
    float scaleXAt1C;
    float scaleYAt20;
    float scaleZAt24;
    float rotationXAt28;
    float rotationYAt2C;
    float rotationZAt30;
    float pivotXAt34;
    float pivotYAt38;
    float pivotZAt3C;
};
typedef char F1094SizeCheck[sizeof(FighterRenderTransformWindowF1094)==36?1:-1];
typedef char F1094PivotOffsetCheck[offsetof(FighterRenderTransformWindowF1094,pivotXAt34)==24?1:-1];
typedef char F1094RotationOffsetCheck[offsetof(FighterRenderTransformWindowF1094,rotationXAt28)==12?1:-1];
#define F1094_TRANSFORM(actor) (*reinterpret_cast<FighterRenderTransformWindowF1094*>(reinterpret_cast<unsigned char*>(actor)+0x1C))
