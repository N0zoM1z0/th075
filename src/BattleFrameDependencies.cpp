#include "BattleScene.hpp"
#include "BattleFrameDependencies.hpp"
#include "BattleStatusFloatPairF1096.hpp"
#define COLLISION reinterpret_cast<BattleScene *>(this)
signed char g_LeftBoundaryOwner = -1;
signed char g_RightBoundaryOwner = -1;

void BattleScene::ResolveBodySeparation()
{
    float vx1 = fighters[0]->velocityX;
    float secondSpeed = fighters[1]->velocityX;
    float meanSpeed;
    signed char boundary[2];
    RECT firstBounds, bounds2;
    int separationDistance;
    boundary[0] = fighters[0]->CheckHorizontalLimits();
    boundary[1] = fighters[1]->CheckHorizontalLimits();
    if (g_RightBoundaryOwner == 0 && boundary[0] != -1) g_RightBoundaryOwner = -1;
    if (g_RightBoundaryOwner == 1 && boundary[1] != -1) g_RightBoundaryOwner = -1;
    if (g_LeftBoundaryOwner == 0 && boundary[0] != 1) g_LeftBoundaryOwner = -1;
    if (g_LeftBoundaryOwner == 1 && boundary[1] != 1) g_LeftBoundaryOwner = -1;
    if (boundary[0] == -1 && g_RightBoundaryOwner < 0) g_RightBoundaryOwner = 0;
    else if (boundary[1] == -1 && g_RightBoundaryOwner < 0) g_RightBoundaryOwner = 1;
    if (boundary[0] == 1 && g_LeftBoundaryOwner < 0) g_LeftBoundaryOwner = 0;
    else if (boundary[1] == 1 && g_LeftBoundaryOwner < 0) g_LeftBoundaryOwner = 1;
    fighters[0]->field488 = 0.0f;
    fighters[1]->field488 = 0.0f;
    COLLISION->TransformBounds(&firstBounds, reinterpret_cast<const RECT *>(&fighters[0]->frameInfo->bodyBox), reinterpret_cast<Actor *>(fighters[0]));
    COLLISION->TransformBounds(&bounds2, reinterpret_cast<const RECT *>(&fighters[1]->frameInfo->bodyBox), reinterpret_cast<Actor *>(fighters[1]));
    if (COLLISION->TestOverlap(&firstBounds, &bounds2)) {
        if (boundary[0] == -1 && g_RightBoundaryOwner == 0) {
            fighters[1]->x -= bounds2.right - firstBounds.left - 1;
            if (fighters[0]->facing * vx1 + fighters[1]->facing * secondSpeed > 0.0f && fighters[1]->facing * secondSpeed > 0.0f) {
                fighters[0]->field488 = -fighters[0]->velocityX;
                fighters[1]->field488 = -fighters[1]->velocityX;
            }
        } else if (boundary[1] == -1 && g_RightBoundaryOwner == 1) {
            fighters[0]->x -= firstBounds.right - bounds2.left - 1;
            if (fighters[0]->facing * vx1 + fighters[1]->facing * secondSpeed > 0.0f && fighters[0]->facing * vx1 > 0.0f) {
                fighters[0]->field488 = -fighters[0]->velocityX;
                fighters[1]->field488 = -fighters[1]->velocityX;
            }
        } else if (boundary[1] == 1 && g_LeftBoundaryOwner == 1) {
            fighters[0]->x += bounds2.right - firstBounds.left - 1;
            if (fighters[1]->facing * secondSpeed + fighters[0]->facing * vx1 < 0.0f && fighters[0]->facing * vx1 < 0.0f) {
                fighters[0]->field488 = -fighters[0]->velocityX;
                fighters[1]->field488 = -fighters[1]->velocityX;
            }
        } else if (boundary[0] == 1 && g_LeftBoundaryOwner == 0) {
            fighters[1]->x += firstBounds.right - bounds2.left - 1;
            if (fighters[0]->facing * vx1 + fighters[1]->facing * secondSpeed < 0.0f && fighters[1]->facing * secondSpeed < 0.0f) {
                fighters[0]->field488 = -fighters[0]->velocityX;
                fighters[1]->field488 = -fighters[1]->velocityX;
            }
        } else if (firstBounds.left + firstBounds.right > bounds2.left + bounds2.right ||
                   (firstBounds.left + firstBounds.right == bounds2.left + bounds2.right && firstBounds.top + firstBounds.bottom < bounds2.top + bounds2.bottom)) {
            if (fighters[0]->velocityX * fighters[0]->facing <= fighters[1]->velocityX * fighters[1]->facing) {
                separationDistance = bounds2.right - firstBounds.left - 1;
                fighters[0]->x += separationDistance / 2.0f;
                fighters[1]->x -= separationDistance / 2.0f;
                meanSpeed = (fighters[0]->facing * vx1 + fighters[1]->facing * secondSpeed) / 2.0f;
                vx1 = fighters[0]->facing * meanSpeed;
                secondSpeed = fighters[1]->facing * meanSpeed;
                fighters[0]->field488 = vx1 - fighters[0]->velocityX;
                fighters[1]->field488 = secondSpeed - fighters[1]->velocityX;
            }
        } else {
            if (fighters[1]->velocityX * fighters[1]->facing <= fighters[0]->velocityX * fighters[0]->facing) {
                separationDistance = firstBounds.right - bounds2.left - 1;
                fighters[0]->x -= separationDistance / 2.0f;
                fighters[1]->x += separationDistance / 2.0f;
                meanSpeed = (fighters[0]->facing * vx1 + fighters[1]->facing * secondSpeed) / 2.0f;
                vx1 = fighters[0]->facing * meanSpeed;
                secondSpeed = fighters[1]->facing * meanSpeed;
                fighters[0]->field488 = vx1 - fighters[0]->velocityX;
                fighters[1]->field488 = secondSpeed - fighters[1]->velocityX;
            }
        }
    }
}

#include "BattleStateMachine.hpp"
#define SLOT(type, offset) reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset)[i]
void BattleScene::UpdateTransition()
{
    int i;
    if (field09C > 0.33f && (fighters[0]->field3A0 > 0 || fighters[1]->field3A0 > 0))
        field09C -= 0.02f;
    for (i = 0; i < 2; ++i) {
        if ((fighters[i]->field3A0) > 0) {
            if ((fighters[i]->field3A2) < 80) {
                if ((fighters[i]->field3A2) == 0) {
                    SLOT(unsigned char, 0xDC) = 15;
                    SLOT(unsigned char, 0xDE) = 5;
                    SLOT(unsigned char, 0xE0) = 5;
                    F1096_STATUS_FLOAT(this, 0xF4, i) = 351.0f;
                    F1096_STATUS_FLOAT(this, 0x104, i) = 12.0f;
                    F1096_STATUS_FLOAT(this, 0xE4, i) = 7.0f;
                    F1096_STATUS_FLOAT(this, 0xFC, i) = 20.0f;
                    SLOT(int, 0xEC) = (fighters[i]->field3A0);
                }
                if (F1096_STATUS_FLOAT(this, 0xFC, i) > 0.0f && (fighters[i]->field3A2) >= 40) {
                    F1096_STATUS_FLOAT(this, 0xF4, i) -= F1096_STATUS_FLOAT(this, 0xFC, i);
                    F1096_STATUS_FLOAT(this, 0xFC, i) -= 0.75f;
                }
                if (SLOT(unsigned char, 0xDC) < 255) SLOT(unsigned char, 0xDC) += 12;
                if (SLOT(unsigned char, 0xDE) < 255) SLOT(unsigned char, 0xDE) += 25;
                if (SLOT(unsigned char, 0xE0) < 255 && (fighters[i]->field3A2) >= 20) SLOT(unsigned char, 0xE0) += 25;
                if (F1096_STATUS_FLOAT(this, 0x104, i) > 0.0f && (fighters[i]->field3A2) >= 30) F1096_STATUS_FLOAT(this, 0x104, i) -= 1.2f;
                if (F1096_STATUS_FLOAT(this, 0xE4, i) > 1.0f) {
                    F1096_STATUS_FLOAT(this, 0xE4, i) -= 0.2f;
                    if (F1096_STATUS_FLOAT(this, 0xE4, i) < 1.0f) F1096_STATUS_FLOAT(this, 0xE4, i) = 1.0f;
                }
            }
            ++(fighters[i]->field3A2);
        }
    }
}

#define OVERLAY_TIME field060
void BattleScene::AdvanceOverlay()
{
    if (OVERLAY_TIME > 0) {
        switch (field064) {
        case 0:
            if (OVERLAY_TIME >= 150) {
                field074 = 350.0f; field070 = 430.0f; field078 = 300.0f;
                field07C = -300.0f; field080 = 0.0f; field084 = 0.0f; field088 = 0.0f;
            } else if (OVERLAY_TIME >= 140) {
                field074 -= 40.0f; field070 -= 70.0f; field078 -= 30.0f;
            } else if (OVERLAY_TIME >= 75) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 0.3f;
                field080 += field084; field084 += 0.05f;
            } else if (OVERLAY_TIME >= 70) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 0.3f;
                field07C += 30.0f; field088 += 0.2f;
            } else if (OVERLAY_TIME >= 65) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 30.0f;
                field07C += 30.0f; field088 += 0.15f;
            } else if (OVERLAY_TIME >= 60) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 30.0f;
                field07C += 0.5f; field088 += 0.15f;
            } else if (OVERLAY_TIME >= 10) {
                field074 -= 30.0f; field070 -= 30.0f; field078 -= 30.0f;
                field07C += 0.5f; field088 += 0.15f;
            } else if (OVERLAY_TIME > 0) {
                field074 -= 30.0f; field070 -= 30.0f; field078 -= 30.0f;
                field07C += 0.5f; field07C += 200.0f;
            }
            break;
        case 1:
            if (OVERLAY_TIME >= 150) {
                field074 = 350.0f; field070 = 430.0f; field078 = 300.0f;
                field07C = -300.0f; field080 = 0.0f; field084 = 0.0f; field088 = 0.0f;
            } else if (OVERLAY_TIME >= 140) {
                field074 -= 40.0f; field070 -= 70.0f; field078 -= 30.0f;
            } else if (OVERLAY_TIME >= 75) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 0.3f;
                field088 += 0.15f;
            } else if (OVERLAY_TIME >= 70) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 0.3f;
                field07C += 30.0f; field088 += 0.15f;
            } else if (OVERLAY_TIME >= 65) {
                field074 -= 0.3f; field070 -= 0.3f; field078 -= 30.0f;
                field07C += 30.0f; field088 += 0.15f;
            } else if (OVERLAY_TIME > 0) {
                field074 -= 30.0f; field070 -= 30.0f; field078 -= 30.0f;
                field088 += 0.15f;
            }
            break;
        }
        --OVERLAY_TIME;
    }
}
