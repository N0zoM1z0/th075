#include "battle/BattleScene.hpp"
#include "battle/BattleFrameDependencies.hpp"
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

#include "battle/BattleStateMachine.hpp"
void BattleScene::UpdateTransition()
{
    int i;
    if (spellBackgroundBrightness > 0.33f && (fighters[0]->spellTimer > 0 || fighters[1]->spellTimer > 0))
        spellBackgroundBrightness -= 0.02f;
    for (i = 0; i < 2; ++i) {
        if ((fighters[i]->spellTimer) > 0) {
            if ((fighters[i]->field3A2) < 80) {
                if ((fighters[i]->field3A2) == 0) {
                    spellPanelAlpha[i] = 15;
                    spellTitleAlpha[i] = 5;
                    spellNumbersAlpha[i] = 5;
                    spellPanelY[i] = 351.0f;
                    spellNumbersOffsetY[i] = 12.0f;
                    spellTitleScale[i] = 7.0f;
                    spellPanelRiseSpeed[i] = 20.0f;
                    initialSpellTimer[i] = (fighters[i]->spellTimer);
                }
                if (spellPanelRiseSpeed[i] > 0.0f && (fighters[i]->field3A2) >= 40) {
                    spellPanelY[i] -= spellPanelRiseSpeed[i];
                    spellPanelRiseSpeed[i] -= 0.75f;
                }
                if (spellPanelAlpha[i] < 255) spellPanelAlpha[i] += 12;
                if (spellTitleAlpha[i] < 255) spellTitleAlpha[i] += 25;
                if (spellNumbersAlpha[i] < 255 && (fighters[i]->field3A2) >= 20) spellNumbersAlpha[i] += 25;
                if (spellNumbersOffsetY[i] > 0.0f && (fighters[i]->field3A2) >= 30) spellNumbersOffsetY[i] -= 1.2f;
                if (spellTitleScale[i] > 1.0f) {
                    spellTitleScale[i] -= 0.2f;
                    if (spellTitleScale[i] < 1.0f) spellTitleScale[i] = 1.0f;
                }
            }
            ++(fighters[i]->field3A2);
        }
    }
}

void BattleScene::AdvanceOverlay()
{
    if (noticeFrames > 0) {
        switch (noticeKind) {
        case 0:
            if (noticeFrames >= 150) {
                noticeHorizontalEdgeOffset = 350.0f; noticeVerticalEdgeOffset = 430.0f; noticeTitleMotion = 300.0f;
                noticeSubtitleMotion = -300.0f; noticeFlashScale = 0.0f; noticeFlashScaleStep = 0.0f; noticePulseScale = 0.0f;
            } else if (noticeFrames >= 140) {
                noticeHorizontalEdgeOffset -= 40.0f; noticeVerticalEdgeOffset -= 70.0f; noticeTitleMotion -= 30.0f;
            } else if (noticeFrames >= 75) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 0.3f;
                noticeFlashScale += noticeFlashScaleStep; noticeFlashScaleStep += 0.05f;
            } else if (noticeFrames >= 70) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 0.3f;
                noticeSubtitleMotion += 30.0f; noticePulseScale += 0.2f;
            } else if (noticeFrames >= 65) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 30.0f;
                noticeSubtitleMotion += 30.0f; noticePulseScale += 0.15f;
            } else if (noticeFrames >= 60) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 30.0f;
                noticeSubtitleMotion += 0.5f; noticePulseScale += 0.15f;
            } else if (noticeFrames >= 10) {
                noticeHorizontalEdgeOffset -= 30.0f; noticeVerticalEdgeOffset -= 30.0f; noticeTitleMotion -= 30.0f;
                noticeSubtitleMotion += 0.5f; noticePulseScale += 0.15f;
            } else if (noticeFrames > 0) {
                noticeHorizontalEdgeOffset -= 30.0f; noticeVerticalEdgeOffset -= 30.0f; noticeTitleMotion -= 30.0f;
                noticeSubtitleMotion += 0.5f; noticeSubtitleMotion += 200.0f;
            }
            break;
        case 1:
            if (noticeFrames >= 150) {
                noticeHorizontalEdgeOffset = 350.0f; noticeVerticalEdgeOffset = 430.0f; noticeTitleMotion = 300.0f;
                noticeSubtitleMotion = -300.0f; noticeFlashScale = 0.0f; noticeFlashScaleStep = 0.0f; noticePulseScale = 0.0f;
            } else if (noticeFrames >= 140) {
                noticeHorizontalEdgeOffset -= 40.0f; noticeVerticalEdgeOffset -= 70.0f; noticeTitleMotion -= 30.0f;
            } else if (noticeFrames >= 75) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 0.3f;
                noticePulseScale += 0.15f;
            } else if (noticeFrames >= 70) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 0.3f;
                noticeSubtitleMotion += 30.0f; noticePulseScale += 0.15f;
            } else if (noticeFrames >= 65) {
                noticeHorizontalEdgeOffset -= 0.3f; noticeVerticalEdgeOffset -= 0.3f; noticeTitleMotion -= 30.0f;
                noticeSubtitleMotion += 30.0f; noticePulseScale += 0.15f;
            } else if (noticeFrames > 0) {
                noticeHorizontalEdgeOffset -= 30.0f; noticeVerticalEdgeOffset -= 30.0f; noticeTitleMotion -= 30.0f;
                noticePulseScale += 0.15f;
            }
            break;
        }
        --noticeFrames;
    }
}
