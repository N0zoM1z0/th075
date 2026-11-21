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

class NativeBackgroundBaseF479 {
public:
    virtual ~NativeBackgroundBaseF479();
    CameraResetF481 cameraReset;
    BackgroundStageParameterFieldsF933 parameters;
    TextureManagerF198 textureManager;
};

typedef char NativeBackgroundBaseSizeF479[
    (sizeof(NativeBackgroundBaseF479) == 0x68) ? 1 : -1];
typedef char NativeBackgroundBaseMembersSizeF479[
    (sizeof(CameraResetF481) +
     sizeof(BackgroundStageParameterFieldsF933) +
     sizeof(TextureManagerF198)) == 0x64 ? 1 : -1];
