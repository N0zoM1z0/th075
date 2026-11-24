#include "CameraUpdate4126C0.hpp"

float __cdecl AbsFloatAt00412D90(float value);

float* g_CameraFirstXAt006713C8;
float* g_CameraSecondXAt006713CC;
float* g_CameraFirstYAt006713D0;
float* g_CameraSecondYAt006713D4;
float g_CameraHorizontalBiasAt006713EC;
float g_CameraHorizontalTargetAt006713F0;
float g_CameraHorizontalAt006713E4;
float g_CameraHorizontalOverrideAt006713E8;
unsigned char g_CameraOverrideEnabledAt00671414;
float g_CameraVerticalBiasAt0067140C;
float g_CameraVerticalTargetAt00671400;
float g_CameraVerticalOverrideAt006713BC;
float g_CameraVerticalAt00671408;
float g_CameraShakeAmountAt006713F8;
float g_CameraShakePhaseXAt00671410;
float g_CameraShakePhaseYAt006713FC;
float g_CameraShakeXAt006713E0;
float g_CameraShakeYAt006713D8;
float g_CameraZoomTargetAt006713C0;
float g_CameraZoomOverrideAt006713F4;
float g_CombatViewSpan;
float g_CombatViewOffsetX;
float g_CombatViewOffsetY;

void CameraUpdate4126C0::Advance() {
    g_CameraHorizontalTargetAt006713F0 = 640.0f -
        ((50.0f - g_CameraHorizontalBiasAt006713EC) * *g_CameraFirstXAt006713C8 +
         (50.0f + g_CameraHorizontalBiasAt006713EC) * *g_CameraSecondXAt006713CC) / 100.0f;
    if (g_CameraHorizontalTargetAt006713F0 < -320.0f)
        g_CameraHorizontalTargetAt006713F0 = -320.0f;
    if (g_CameraHorizontalTargetAt006713F0 > 320.0f)
        g_CameraHorizontalTargetAt006713F0 = 320.0f;
    if (g_CameraOverrideEnabledAt00671414)
        g_CameraHorizontalTargetAt006713F0 = g_CameraHorizontalOverrideAt006713E8;
    if (g_CameraHorizontalAt006713E4 < g_CameraHorizontalTargetAt006713F0) {
        g_CameraHorizontalAt006713E4 -=
            (g_CameraHorizontalAt006713E4 - g_CameraHorizontalTargetAt006713F0) / 30.0f - 5.0f;
        if (g_CameraHorizontalAt006713E4 > g_CameraHorizontalTargetAt006713F0)
            g_CameraHorizontalAt006713E4 = g_CameraHorizontalTargetAt006713F0;
    } else {
        g_CameraHorizontalAt006713E4 -=
            (g_CameraHorizontalAt006713E4 - g_CameraHorizontalTargetAt006713F0) / 30.0f + 5.0f;
        if (g_CameraHorizontalAt006713E4 < g_CameraHorizontalTargetAt006713F0)
            g_CameraHorizontalAt006713E4 = g_CameraHorizontalTargetAt006713F0;
    }

    int span = static_cast<int>(880.0f - AbsFloatAt00412D90(
        *g_CameraFirstXAt006713C8 - *g_CameraSecondXAt006713CC));
    if (span > 320)
        span = 320;
    else if (span < 0)
        span = 0;

    g_CameraVerticalTargetAt00671400 = AbsFloatAt00412D90(
        (50.0f - g_CameraVerticalBiasAt0067140C) * *g_CameraFirstYAt006713D0 -
        (50.0f + g_CameraVerticalBiasAt0067140C) * *g_CameraSecondYAt006713D4) / 100.0f;
    if (span / 3 < g_CameraVerticalTargetAt00671400)
        g_CameraVerticalTargetAt00671400 = span / 3;
    if (g_CameraOverrideEnabledAt00671414)
        g_CameraVerticalTargetAt00671400 = g_CameraVerticalOverrideAt006713BC;
    if (g_CameraVerticalAt00671408 < g_CameraVerticalTargetAt00671400) {
        g_CameraVerticalAt00671408 -=
            (g_CameraVerticalAt00671408 - g_CameraVerticalTargetAt00671400) / 20.0f - 1.0f;
        if (g_CameraVerticalAt00671408 > g_CameraVerticalTargetAt00671400)
            g_CameraVerticalAt00671408 = g_CameraVerticalTargetAt00671400;
    } else {
        g_CameraVerticalAt00671408 -=
            (g_CameraVerticalAt00671408 - g_CameraVerticalTargetAt00671400) / 20.0f + 1.0f;
        if (g_CameraVerticalAt00671408 < g_CameraVerticalTargetAt00671400)
            g_CameraVerticalAt00671408 = g_CameraVerticalTargetAt00671400;
    }

    if (g_CameraShakeAmountAt006713F8 >= 1.0f) {
        g_CameraShakeXAt006713E0 = CameraCosineAt0040D900(
            g_CameraShakePhaseXAt00671410 * 0.01745328866f) * g_CameraShakeAmountAt006713F8;
        g_CameraShakeYAt006713D8 = CameraSineAt0040D940(
            g_CameraShakePhaseYAt006713FC * 0.01745328866f) * g_CameraShakeAmountAt006713F8;
        g_CameraShakePhaseXAt00671410 += 83.0f;
        if (g_CameraShakePhaseXAt00671410 >= 360.0f)
            g_CameraShakePhaseXAt00671410 -= 360.0f;
        g_CameraShakePhaseYAt006713FC += 107.0f;
        if (g_CameraShakePhaseYAt006713FC >= 360.0f)
            g_CameraShakePhaseYAt006713FC -= 360.0f;
        g_CameraShakeAmountAt006713F8 *= 0.95f;
        if (g_CameraShakeAmountAt006713F8 < 1.0f) {
            g_CameraShakeAmountAt006713F8 = 0.0f;
            g_CameraShakeXAt006713E0 = 0.0f;
            g_CameraShakeYAt006713D8 = 0.0f;
        }
    }

    g_CameraZoomTargetAt006713C0 = 880.0f - AbsFloatAt00412D90(
        *g_CameraFirstXAt006713C8 - *g_CameraSecondXAt006713CC);
    if (g_CameraOverrideEnabledAt00671414)
        g_CameraZoomTargetAt006713C0 = g_CameraZoomOverrideAt006713F4;
    if (g_CameraZoomTargetAt006713C0 > 320.0f)
        g_CameraZoomTargetAt006713C0 = 320.0f;
    else if (AbsFloatAt00412D90(
                 320.0f * g_CameraHorizontalBiasAt006713EC / 50.0f) + 0.0f > g_CameraZoomTargetAt006713C0)
        g_CameraZoomTargetAt006713C0 = AbsFloatAt00412D90(
            320.0f * g_CameraHorizontalBiasAt006713EC / 50.0f) + 0.0f;
    if (g_CombatViewSpan > g_CameraZoomTargetAt006713C0) {
        g_CombatViewSpan -= (g_CombatViewSpan - g_CameraZoomTargetAt006713C0) / 40.0f + 11.0f;
        if (g_CombatViewSpan < g_CameraZoomTargetAt006713C0)
            g_CombatViewSpan = g_CameraZoomTargetAt006713C0;
    } else {
        g_CombatViewSpan -= (g_CombatViewSpan - g_CameraZoomTargetAt006713C0) / 40.0f - 11.0f;
        if (g_CombatViewSpan > g_CameraZoomTargetAt006713C0)
            g_CombatViewSpan = g_CameraZoomTargetAt006713C0;
    }

    if (g_CameraHorizontalBiasAt006713EC < 0.0f) {
        g_CameraHorizontalBiasAt006713EC += 10.0f;
        if (g_CameraHorizontalBiasAt006713EC > 0.0f)
            g_CameraHorizontalBiasAt006713EC = 0.0f;
    } else if (g_CameraHorizontalBiasAt006713EC > 0.0f) {
        g_CameraHorizontalBiasAt006713EC -= 10.0f;
        if (g_CameraHorizontalBiasAt006713EC < 0.0f)
            g_CameraHorizontalBiasAt006713EC = 0.0f;
    }
    if (*g_CameraFirstYAt006713D0 > *g_CameraSecondYAt006713D4)
        g_CameraVerticalBiasAt0067140C = 40.0f;
    else if (*g_CameraFirstYAt006713D0 < *g_CameraSecondYAt006713D4)
        g_CameraVerticalBiasAt0067140C = -40.0f;
    g_CombatViewOffsetX = g_CameraHorizontalAt006713E4 + g_CameraShakeXAt006713E0;
    g_CombatViewOffsetY = g_CameraVerticalAt00671408 + g_CameraShakeYAt006713D8 + 300.0f;
}
