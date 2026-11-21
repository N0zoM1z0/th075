// Reimu Fighter::Advance native action 0x2E6 at 0045DD70.
// Four difficulty-scaled radial patterns, random paired effects, six burst
// children, and the original stage/counter loops remain ordinary C++.
case 0x2E6: {
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        field07C = 0;
        field3AC = 0;
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        fieldF04 = 0;
        fieldF06 = 0x1E;
        fieldF08 = 1;
        field05C = 0.15f;
    }
    if (animationStage == 6 || animationStage == 7) {
        if (color[0] < 0x1F) {
            color[0] = 0;
            ResetSecondaryCounter(8);
            return;
        }
        color[0] = static_cast<unsigned char>(color[0] - 0x1E);
    }
    if (animationStage == 8 && animationFrame == 0) {
        velocityX = static_cast<float>(RecordedRange(0, 100) - 0x32);
        velocityY = static_cast<float>(RecordedRange(0, 5) + 0x14);
        facing = x <= opponent->x ? 1 : -1;
    }
    if (animationStage == 9) {
        if (color[0] < 0xE1) color[0] = static_cast<unsigned char>(color[0] + 0x1E);
        else color[0] = 0xFF;
    }
    if (animationStage > 0x0D && animationStage < 0x13 &&
        g_ThresholdAt0065782C < y) {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            color[0] = 0xFF;
            ClearMotionFields();
            ResetSecondaryCounter(0x13);
            y = 0.0f;
            return;
        }
    }
    if (animationStage > 1 && animationStage < 8) {
        Fighter::SpawnTrackedEffect(0x33E,
            static_cast<float>(RecordedRange(0, 120)) + x - g_ReimuStormPairXBaseAt00658264,
            y - g_ReimuStormPairYBaseAt00657CBC + static_cast<float>(RecordedRange(0, 90)),
            1, 1, 0, 1);
    }
    if (animationStage > 0x0A && animationStage < 0x11 && scriptCounterF02 == 0) {
        ++scriptCounterF02;
        if (g_ReimuRepeatSettingAt006714D0 == 0) {
            for (int shot = 0; shot < 12; ++shot) {
                field314 = static_cast<float>(shot * 30);
                SpawnBattleEffect(0x387, x - static_cast<float>(facing * 16),
                    y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        if (g_ReimuRepeatSettingAt006714D0 == 1) {
            for (int shot = 0; shot < 20; ++shot) {
                field314 = static_cast<float>(shot * 18);
                SpawnBattleEffect(0x387, x - static_cast<float>(facing * 16),
                    y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        if (g_ReimuRepeatSettingAt006714D0 == 2) {
            for (int shot = 0; shot < 30; ++shot) {
                field314 = static_cast<float>(shot * 12);
                SpawnBattleEffect(0x387, x - static_cast<float>(facing * 16),
                    y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
        if (g_ReimuRepeatSettingAt006714D0 == 3) {
            for (int shot = 0; shot < 40; ++shot) {
                field314 = static_cast<float>(shot * 9);
                SpawnBattleEffect(0x387, x - static_cast<float>(facing * 16),
                    y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
            }
        }
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        aiCardTimer = static_cast<short>(RecordedRange(60, 120) -
            g_ReimuRepeatSettingAt006714D0 * 20);
    }
    if (animationStage == 6 && animationFrame == 0) {
        PlaySound(2);
        Fighter::SpawnTrackedEffect(0x338, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x339, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33A, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33B, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33C, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33D, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        ResetTransform(0.0f, 0.0f, 0.0f);
        color[0] = 0xFF;
    }
    if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF00;
        return;
    }
    if (animationStage == 9 && animationFrame == 0) {
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 0x0B && animationFrame == 0) PlaySound(5);
    if (animationStage == 0x11 && animationFrame == 0 && scriptCounterF00 < 10) {
        ResetSecondaryCounter(0x0F);
        ++scriptCounterF00;
    }
    if (animationStage == 0x13 && animationFrame == 0) ResetSecondaryCounter(0x11);
    return;
}
