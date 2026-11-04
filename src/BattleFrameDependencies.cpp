#include "BattleFrameDependencies.hpp"
#include "FrameActorMotionPairsF1037.hpp"
#include "BattleStatusFloatPairF1096.hpp"
#include "StateOverlayFloatWindowF1106.hpp"
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define PLAYER(offset) FIELD(FrameActor *, this, offset)
#define ACTOR(type, offset, field) FIELD(type, PLAYER(offset), field)
#define COLLISION reinterpret_cast<BattleCollision *>(this)
void BattleFrame::ResolveBodySeparation()
{
    float vx1 = F1037_MOTION(PLAYER(0x44)).xMotion;
    float secondSpeed = F1037_MOTION(PLAYER(0x48)).xMotion;
    float meanSpeed;
    signed char boundary[2];
    RECT firstBounds, bounds2;
    int separationDistance;
    boundary[0] = PLAYER(0x44)->CheckHorizontalLimits();
    boundary[1] = PLAYER(0x48)->CheckHorizontalLimits();
    if (g_RightBoundaryOwner == 0 && boundary[0] != -1) g_RightBoundaryOwner = -1;
    if (g_RightBoundaryOwner == 1 && boundary[1] != -1) g_RightBoundaryOwner = -1;
    if (g_LeftBoundaryOwner == 0 && boundary[0] != 1) g_LeftBoundaryOwner = -1;
    if (g_LeftBoundaryOwner == 1 && boundary[1] != 1) g_LeftBoundaryOwner = -1;
    if (boundary[0] == -1 && g_RightBoundaryOwner < 0) g_RightBoundaryOwner = 0;
    else if (boundary[1] == -1 && g_RightBoundaryOwner < 0) g_RightBoundaryOwner = 1;
    if (boundary[0] == 1 && g_LeftBoundaryOwner < 0) g_LeftBoundaryOwner = 0;
    else if (boundary[1] == 1 && g_LeftBoundaryOwner < 0) g_LeftBoundaryOwner = 1;
    ACTOR(float, 0x44, 0x488) = 0.0f;
    ACTOR(float, 0x48, 0x488) = 0.0f;
    COLLISION->TransformBounds(&firstBounds, reinterpret_cast<const RECT *>(reinterpret_cast<unsigned char *>(ACTOR(void *, 0x44, 0x74)) + 0x44), reinterpret_cast<CombatActor *>(PLAYER(0x44)));
    COLLISION->TransformBounds(&bounds2, reinterpret_cast<const RECT *>(reinterpret_cast<unsigned char *>(ACTOR(void *, 0x48, 0x74)) + 0x44), reinterpret_cast<CombatActor *>(PLAYER(0x48)));
    if (COLLISION->TestOverlap(&firstBounds, &bounds2)) {
        if (boundary[0] == -1 && g_RightBoundaryOwner == 0) {
            F1037_POSITION(PLAYER(0x48)).xPosition -= bounds2.right - firstBounds.left - 1;
            if (ACTOR(signed char, 0x44, 0x66) * vx1 + ACTOR(signed char, 0x48, 0x66) * secondSpeed > 0.0f && ACTOR(signed char, 0x48, 0x66) * secondSpeed > 0.0f) {
                ACTOR(float, 0x44, 0x488) = -F1037_MOTION(PLAYER(0x44)).xMotion;
                ACTOR(float, 0x48, 0x488) = -F1037_MOTION(PLAYER(0x48)).xMotion;
            }
        } else if (boundary[1] == -1 && g_RightBoundaryOwner == 1) {
            F1037_POSITION(PLAYER(0x44)).xPosition -= firstBounds.right - bounds2.left - 1;
            if (ACTOR(signed char, 0x44, 0x66) * vx1 + ACTOR(signed char, 0x48, 0x66) * secondSpeed > 0.0f && ACTOR(signed char, 0x44, 0x66) * vx1 > 0.0f) {
                ACTOR(float, 0x44, 0x488) = -F1037_MOTION(PLAYER(0x44)).xMotion;
                ACTOR(float, 0x48, 0x488) = -F1037_MOTION(PLAYER(0x48)).xMotion;
            }
        } else if (boundary[1] == 1 && g_LeftBoundaryOwner == 1) {
            F1037_POSITION(PLAYER(0x44)).xPosition += bounds2.right - firstBounds.left - 1;
            if (ACTOR(signed char, 0x48, 0x66) * secondSpeed + ACTOR(signed char, 0x44, 0x66) * vx1 < 0.0f && ACTOR(signed char, 0x44, 0x66) * vx1 < 0.0f) {
                ACTOR(float, 0x44, 0x488) = -F1037_MOTION(PLAYER(0x44)).xMotion;
                ACTOR(float, 0x48, 0x488) = -F1037_MOTION(PLAYER(0x48)).xMotion;
            }
        } else if (boundary[0] == 1 && g_LeftBoundaryOwner == 0) {
            F1037_POSITION(PLAYER(0x48)).xPosition += firstBounds.right - bounds2.left - 1;
            if (ACTOR(signed char, 0x44, 0x66) * vx1 + ACTOR(signed char, 0x48, 0x66) * secondSpeed < 0.0f && ACTOR(signed char, 0x48, 0x66) * secondSpeed < 0.0f) {
                ACTOR(float, 0x44, 0x488) = -F1037_MOTION(PLAYER(0x44)).xMotion;
                ACTOR(float, 0x48, 0x488) = -F1037_MOTION(PLAYER(0x48)).xMotion;
            }
        } else if (firstBounds.left + firstBounds.right > bounds2.left + bounds2.right ||
                   (firstBounds.left + firstBounds.right == bounds2.left + bounds2.right && firstBounds.top + firstBounds.bottom < bounds2.top + bounds2.bottom)) {
            if (F1037_MOTION(PLAYER(0x44)).xMotion * ACTOR(signed char, 0x44, 0x66) <= F1037_MOTION(PLAYER(0x48)).xMotion * ACTOR(signed char, 0x48, 0x66)) {
                separationDistance = bounds2.right - firstBounds.left - 1;
                F1037_POSITION(PLAYER(0x44)).xPosition += separationDistance / 2.0f;
                F1037_POSITION(PLAYER(0x48)).xPosition -= separationDistance / 2.0f;
                meanSpeed = (ACTOR(signed char, 0x44, 0x66) * vx1 + ACTOR(signed char, 0x48, 0x66) * secondSpeed) / 2.0f;
                vx1 = ACTOR(signed char, 0x44, 0x66) * meanSpeed;
                secondSpeed = ACTOR(signed char, 0x48, 0x66) * meanSpeed;
                ACTOR(float, 0x44, 0x488) = vx1 - F1037_MOTION(PLAYER(0x44)).xMotion;
                ACTOR(float, 0x48, 0x488) = secondSpeed - F1037_MOTION(PLAYER(0x48)).xMotion;
            }
        } else {
            if (F1037_MOTION(PLAYER(0x48)).xMotion * ACTOR(signed char, 0x48, 0x66) <= F1037_MOTION(PLAYER(0x44)).xMotion * ACTOR(signed char, 0x44, 0x66)) {
                separationDistance = firstBounds.right - bounds2.left - 1;
                F1037_POSITION(PLAYER(0x44)).xPosition -= separationDistance / 2.0f;
                F1037_POSITION(PLAYER(0x48)).xPosition += separationDistance / 2.0f;
                meanSpeed = (ACTOR(signed char, 0x44, 0x66) * vx1 + ACTOR(signed char, 0x48, 0x66) * secondSpeed) / 2.0f;
                vx1 = ACTOR(signed char, 0x44, 0x66) * meanSpeed;
                secondSpeed = ACTOR(signed char, 0x48, 0x66) * meanSpeed;
                ACTOR(float, 0x44, 0x488) = vx1 - F1037_MOTION(PLAYER(0x44)).xMotion;
                ACTOR(float, 0x48, 0x488) = secondSpeed - F1037_MOTION(PLAYER(0x48)).xMotion;
            }
        }
    }
}

#include "BattleStateMachine.hpp"
#define SLOT(type, offset) reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset)[i]
#define INDEXED_PLAYER SLOT(FrameActor *, 0x44)
#define TIMER_FIELD(offset) FIELD(short, INDEXED_PLAYER, offset)
void StateFramePolicies::UpdateTransition()
{
    int i;
    if (FIELD(float, this, 0x9C) > 0.33f && (ACTOR(short, 0x44, 0x3A0) > 0 || ACTOR(short, 0x48, 0x3A0) > 0))
        FIELD(float, this, 0x9C) -= 0.02f;
    for (i = 0; i < 2; ++i) {
        if (TIMER_FIELD(0x3A0) > 0) {
            if (TIMER_FIELD(0x3A2) < 80) {
                if (TIMER_FIELD(0x3A2) == 0) {
                    SLOT(unsigned char, 0xDC) = 15;
                    SLOT(unsigned char, 0xDE) = 5;
                    SLOT(unsigned char, 0xE0) = 5;
                    F1096_STATUS_FLOAT(this, 0xF4, i) = 351.0f;
                    F1096_STATUS_FLOAT(this, 0x104, i) = 12.0f;
                    F1096_STATUS_FLOAT(this, 0xE4, i) = 7.0f;
                    F1096_STATUS_FLOAT(this, 0xFC, i) = 20.0f;
                    SLOT(int, 0xEC) = TIMER_FIELD(0x3A0);
                }
                if (F1096_STATUS_FLOAT(this, 0xFC, i) > 0.0f && TIMER_FIELD(0x3A2) >= 40) {
                    F1096_STATUS_FLOAT(this, 0xF4, i) -= F1096_STATUS_FLOAT(this, 0xFC, i);
                    F1096_STATUS_FLOAT(this, 0xFC, i) -= 0.75f;
                }
                if (SLOT(unsigned char, 0xDC) < 255) SLOT(unsigned char, 0xDC) += 12;
                if (SLOT(unsigned char, 0xDE) < 255) SLOT(unsigned char, 0xDE) += 25;
                if (SLOT(unsigned char, 0xE0) < 255 && TIMER_FIELD(0x3A2) >= 20) SLOT(unsigned char, 0xE0) += 25;
                if (F1096_STATUS_FLOAT(this, 0x104, i) > 0.0f && TIMER_FIELD(0x3A2) >= 30) F1096_STATUS_FLOAT(this, 0x104, i) -= 1.2f;
                if (F1096_STATUS_FLOAT(this, 0xE4, i) > 1.0f) {
                    F1096_STATUS_FLOAT(this, 0xE4, i) -= 0.2f;
                    if (F1096_STATUS_FLOAT(this, 0xE4, i) < 1.0f) F1096_STATUS_FLOAT(this, 0xE4, i) = 1.0f;
                }
            }
            ++TIMER_FIELD(0x3A2);
        }
    }
}

#define OVERLAY_TIME FIELD(int, this, 0x60)
#define VALUE(offset) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset)
void StateFramePolicies::AdvanceOverlay()
{
    if (OVERLAY_TIME > 0) {
        switch (FIELD(unsigned char, this, 0x64)) {
        case 0:
            if (OVERLAY_TIME >= 150) {
                F1106_OVERLAY(this).at74 = 350.0f; F1106_OVERLAY(this).at70 = 430.0f; F1106_OVERLAY(this).at78 = 300.0f;
                F1106_OVERLAY(this).at7C = -300.0f; F1106_OVERLAY(this).at80 = 0.0f; F1106_OVERLAY(this).at84 = 0.0f; F1106_OVERLAY(this).at88 = 0.0f;
            } else if (OVERLAY_TIME >= 140) {
                F1106_OVERLAY(this).at74 -= 40.0f; F1106_OVERLAY(this).at70 -= 70.0f; F1106_OVERLAY(this).at78 -= 30.0f;
            } else if (OVERLAY_TIME >= 75) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 0.3f;
                F1106_OVERLAY(this).at80 += F1106_OVERLAY(this).at84; F1106_OVERLAY(this).at84 += 0.05f;
            } else if (OVERLAY_TIME >= 70) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 0.3f;
                F1106_OVERLAY(this).at7C += 30.0f; F1106_OVERLAY(this).at88 += 0.2f;
            } else if (OVERLAY_TIME >= 65) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 30.0f;
                F1106_OVERLAY(this).at7C += 30.0f; F1106_OVERLAY(this).at88 += 0.15f;
            } else if (OVERLAY_TIME >= 60) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 30.0f;
                F1106_OVERLAY(this).at7C += 0.5f; F1106_OVERLAY(this).at88 += 0.15f;
            } else if (OVERLAY_TIME >= 10) {
                F1106_OVERLAY(this).at74 -= 30.0f; F1106_OVERLAY(this).at70 -= 30.0f; F1106_OVERLAY(this).at78 -= 30.0f;
                F1106_OVERLAY(this).at7C += 0.5f; F1106_OVERLAY(this).at88 += 0.15f;
            } else if (OVERLAY_TIME > 0) {
                F1106_OVERLAY(this).at74 -= 30.0f; F1106_OVERLAY(this).at70 -= 30.0f; F1106_OVERLAY(this).at78 -= 30.0f;
                F1106_OVERLAY(this).at7C += 0.5f; F1106_OVERLAY(this).at7C += 200.0f;
            }
            break;
        case 1:
            if (OVERLAY_TIME >= 150) {
                F1106_OVERLAY(this).at74 = 350.0f; F1106_OVERLAY(this).at70 = 430.0f; F1106_OVERLAY(this).at78 = 300.0f;
                F1106_OVERLAY(this).at7C = -300.0f; F1106_OVERLAY(this).at80 = 0.0f; F1106_OVERLAY(this).at84 = 0.0f; F1106_OVERLAY(this).at88 = 0.0f;
            } else if (OVERLAY_TIME >= 140) {
                F1106_OVERLAY(this).at74 -= 40.0f; F1106_OVERLAY(this).at70 -= 70.0f; F1106_OVERLAY(this).at78 -= 30.0f;
            } else if (OVERLAY_TIME >= 75) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 0.3f;
                F1106_OVERLAY(this).at88 += 0.15f;
            } else if (OVERLAY_TIME >= 70) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 0.3f;
                F1106_OVERLAY(this).at7C += 30.0f; F1106_OVERLAY(this).at88 += 0.15f;
            } else if (OVERLAY_TIME >= 65) {
                F1106_OVERLAY(this).at74 -= 0.3f; F1106_OVERLAY(this).at70 -= 0.3f; F1106_OVERLAY(this).at78 -= 30.0f;
                F1106_OVERLAY(this).at7C += 30.0f; F1106_OVERLAY(this).at88 += 0.15f;
            } else if (OVERLAY_TIME > 0) {
                F1106_OVERLAY(this).at74 -= 30.0f; F1106_OVERLAY(this).at70 -= 30.0f; F1106_OVERLAY(this).at78 -= 30.0f;
                F1106_OVERLAY(this).at88 += 0.15f;
            }
            break;
        }
        --OVERLAY_TIME;
    }
}
