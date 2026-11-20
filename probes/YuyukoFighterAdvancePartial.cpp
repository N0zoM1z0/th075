// Partial natural-C++ reconstruction of the Yuyuko fighter move state
// machine at 0x00564BE0. This probe covers the signed horizontal-drift family
// (0x32-0x41) and the long landing state 0x8C. Other recovered states are
// intentionally not claimed; the shared native default path is retained as
// a falsifiable fallback while the remaining action families are recovered.
#include "YuyukoFighter.hpp"

extern float g_ThresholdAt0065782C;
extern float g_JumpGroundCorrectionAt00658058;
extern double g_ContactScaleAt006583E8;
extern float g_SubtractAt00657478;
extern double g_RiseAt00658050;
extern float g_ExtraThresholdAt00657D14;
extern float g_ApproachLowerAt00658290;
extern float g_ApproachUpperAt006592A4;
extern float g_StopThresholdAt00657480;
extern float g_ContactProjectionAt00657888;

void YuyukoFighter::Advance() {
    if (field082 != 0 || opponent->field3BA != 0)
        return;

    switch (action) {
    case 0:
    case 2:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (g_ThresholdAt0065782C < velocityX) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (g_ThresholdAt0065782C < velocityX) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        AdvanceNestedFrame();
        return;

    case 1:
    case 3: {
        short neutralAction = action == 1 ? 2 : 0;
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (g_ThresholdAt0065782C < velocityX) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (g_ThresholdAt0065782C < velocityX) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(neutralAction);
        return;
    }

    case 4:
        velocityX = 4.0f;
        AdvanceNestedFrame();
        return;

    case 5:
        velocityX = -4.0f;
        AdvanceNestedFrame();
        return;

    case 6:
    case 7:
    case 8: {
        short specialAction = action == 6 ? 0xCC : action == 7 ? 0xCD : 0xCE;
        unsigned char command = action == 6 ? 3 : action == 7 ? 5 : 4;
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == command || field3AC > 0)) {
            ResetPrimaryCounters(specialAction);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 2 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = action == 6 ? 0.0f : action == 7 ? 4.0f : -4.0f;
                if (action == 8) field3AC = 0;
                velocityY = 12.0f;
                field05C = 0.4f;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
    }

    case 9:
        if (field05C == g_ThresholdAt0065782C)
            field05C = 0.6f;
        velocityY -= field05C;
        if (y + velocityY > g_ThresholdAt0065782C) {
            if (AdvanceNestedFrame() == animationStageCount)
                ResetSecondaryCounter(0);
        } else {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
        }
        return;

    case 10:
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(inputY == 0 ? 0 : 1);
        return;
    case 0x32:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;

    case 0x33:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x34:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x35:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage != 7 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x38:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x39:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x3A:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x3B:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage != 7 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x3E:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x3F:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x40:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x41:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage != 7 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x46:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY += field098;
            if (velocityY < g_ApproachLowerAt00658290)
                velocityY = 6.0f;
            field05C = 0.8f;
            if (g_ApproachUpperAt006592A4 < velocityY)
                velocityY = 25.0f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x47:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x48:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 1.3f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x49:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage != 1 || animationFrame != 0 || velocityY == 0.0f)
            return;
        ResetSecondaryCounter(velocityX == 0.0f ? 3 : 2);
        return;

    case 0x8C:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 3 || animationFrame != 0 || scriptCounterF00 > 4)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    default:
        // The original common default path advances the nested animation and
        // returns to neutral only when the action's stage sequence wraps.
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }
}
