#include "CameraInputs412660.hpp"
#include "CameraUpdate4126C0.hpp"

void CameraInputs412660::Initialize(float* firstX, float* firstY,
                                       float* secondX, float* secondY) {
    g_CameraFirstXAt006713C8 = firstX;
    g_CameraFirstYAt006713D0 = firstY;
    g_CameraSecondXAt006713CC = secondX;
    g_CameraSecondYAt006713D4 = secondY;
    CameraUpdate4126C0::Advance();
    g_CameraHorizontalAt006713E4 = g_CameraHorizontalTargetAt006713F0;
    g_CameraVerticalAt00671408 = g_CameraVerticalTargetAt00671400;
    g_CombatViewOffsetX = g_CameraHorizontalAt006713E4;
    g_CombatViewOffsetY = g_CameraVerticalAt00671408 + 300.0f;
}
