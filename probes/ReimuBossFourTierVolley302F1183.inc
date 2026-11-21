// Reimu Fighter::Advance native action 0x302 at 0045DD70.
// The native four-tier 0x389 ring keeps its exact 10/12/15/20-shot cadence.
case 0x302: {
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        fieldF04 = 0;
        fieldF08 = static_cast<short>(g_ReimuRepeatSettingAt006714D0 + 2);
    }
    if (animationStage < 0x0D && g_ThresholdAt0065782C < y) {
        velocityY = velocityY - field05C;
        if (velocityY < g_AnimationDeltaAt0065747C) velocityY = g_AnimationDeltaAt0065747C;
    }
    if (animationStage > 0x0C && g_ThresholdAt0065782C < y) {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            y = 0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(0x0F);
        }
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 0xB4 - g_ReimuRepeatSettingAt006714D0 * 20);
    }
    if (animationStage == 2 && animationFrame == 0) {
        velocityY = 13.5f;
        field05C = 0.5f;
    }
    if (animationStage == 5 && animationFrame == 0) {
        PlaySound(5);
        if (g_ReimuRepeatSettingAt006714D0 == 0) {
            for (int shot = 0; shot < 10; ++shot) {
                field314 = static_cast<float>(shot * 36);
                field318 = 4.0f;
                SpawnBattleEffect(0x389, x - static_cast<float>(facing * 16), y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        if (g_ReimuRepeatSettingAt006714D0 == 1) {
            for (int shot = 0; shot < 12; ++shot) {
                field314 = static_cast<float>(shot * 30);
                field318 = 4.0f;
                SpawnBattleEffect(0x389, x - static_cast<float>(facing * 16), y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        if (g_ReimuRepeatSettingAt006714D0 == 2) {
            for (int shot = 0; shot < 15; ++shot) {
                field314 = static_cast<float>(shot * 24);
                field318 = 4.0f;
                SpawnBattleEffect(0x389, x - static_cast<float>(facing * 16), y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        if (g_ReimuRepeatSettingAt006714D0 == 3) {
            for (int shot = 0; shot < 20; ++shot) {
                field314 = static_cast<float>(shot * 18);
                field318 = 4.0f;
                SpawnBattleEffect(0x389, x - static_cast<float>(facing * 16), y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        return;
    }
    return;
}
