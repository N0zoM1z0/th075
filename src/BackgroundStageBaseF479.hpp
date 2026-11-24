#pragma once

#include "CameraResetF481.hpp"
#include "BackgroundStageStateF933.hpp"
#include "TextureManagerF198.hpp"

// Original background-base receiver: native vptr, camera-reset subobject,
// three stage-specific words, then the embedded 80-byte TextureManager.
// The word block has integer-zero and float-initialization views.
union BackgroundStageParameterFieldsF933 {
    BackgroundStageZeroFieldsF933 zero;
    BackgroundStageFloatFieldsF933 floating;
};

class SpriteQuad40CA80;

class NativeBackgroundBaseF479 {
public:
    NativeBackgroundBaseF479();
    virtual ~NativeBackgroundBaseF479();
    virtual void Advance() = 0;
    virtual void Slot2() = 0;
    virtual void Slot3() = 0;
    virtual void Render() = 0;
    virtual void ApplyTransform(SpriteQuad40CA80* destination, DWORD* color, SpriteQuad40CA80* source) = 0;
    void CopyParameters(BackgroundStageFloatFieldsF933* destination);

    CameraResetF481 cameraReset;
    BackgroundStageParameterFieldsF933 parameters;
    TextureManagerF198 textureManager;
};

extern NativeBackgroundBaseF479* g_CurrentBattleStageAt00671424;

typedef char NativeBackgroundBaseSizeF479[
    (sizeof(NativeBackgroundBaseF479) == 0x68) ? 1 : -1];
typedef char NativeBackgroundBaseMembersSizeF479[
    (sizeof(CameraResetF481) +
     sizeof(BackgroundStageParameterFieldsF933) +
     sizeof(TextureManagerF198)) == 0x64 ? 1 : -1];
