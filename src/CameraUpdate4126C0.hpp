#pragma once

namespace CameraUpdate4126C0 {
    void Advance();
}

// Observed cdecl(float), ST0-result views. Original declarations remain unknown.
float __cdecl CameraAbsoluteAt00412D90(float value);
float __cdecl CameraCosineAt0040D900(float radians);
float __cdecl CameraSineAt0040D940(float radians);

extern float* g_CameraFirstXAt006713C8;
extern float* g_CameraSecondXAt006713CC;
extern float* g_CameraFirstYAt006713D0;
extern float* g_CameraSecondYAt006713D4;
extern float g_CameraHorizontalBiasAt006713EC;
extern float g_CameraHorizontalTargetAt006713F0;
extern float g_CameraHorizontalAt006713E4;
extern float g_CameraHorizontalOverrideAt006713E8;
extern unsigned char g_CameraOverrideEnabledAt00671414;
extern float g_CameraVerticalBiasAt0067140C;
extern float g_CameraVerticalTargetAt00671400;
extern float g_CameraVerticalOverrideAt006713BC;
extern float g_CameraVerticalAt00671408;
extern float g_CameraShakeAmountAt006713F8;
extern float g_CameraShakePhaseXAt00671410;
extern float g_CameraShakePhaseYAt006713FC;
extern float g_CameraShakeXAt006713E0;
extern float g_CameraShakeYAt006713D8;
extern float g_CameraZoomTargetAt006713C0;
extern float g_CameraZoomOverrideAt006713F4;
extern float g_CombatViewSpan;
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
