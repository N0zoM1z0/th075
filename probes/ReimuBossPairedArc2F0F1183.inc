// Reimu Fighter::Advance native action 0x2F0 at 0045DD70.
// Five timed 0x38F launches preserve the stored velocity vector during the
// descending paired-arc sequence.
case 0x2F0: {
    if (animationStage == 0 && animationFrame == 0) {
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        fieldF04 = 0;
        field07C = 0;
        ClearMotionFields();
        field080 = 99;
    }
    if (g_ThresholdAt0065782C < y && animationStage < 0x16)
        velocityY = velocityY - g_ReimuFallingGravityAt00658354;
    if (g_ThresholdAt0065782C < y && animationStage > 0x17) {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C && animationStage < 0x22) {
            ResetSecondaryCounter(0x22);
            ClearMotionFields();
            y = 0.0f;
            return;
        }
    }
    if (animationFrame == 0) field07C = 0;
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        aiCardTimer = static_cast<short>(RecordedRange(60, 120));
    }
    if (animationStage == 0x0D && animationFrame == 0) {
        PlaySound(7);
        velocityX = static_cast<float>(RecordedRange(0, 6) - 3);
        velocityY = 3.5f;
        field05C = 0.5f;
    }
    if ((animationStage == 0x0F || animationStage == 0x11 || animationStage == 0x13 ||
         animationStage == 0x15 || animationStage == 0x17) && animationFrame == 0) {
        scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
        scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
        field314 = static_cast<float>(RecordedRange(0, 100) - 0x46);
        field318 = static_cast<float>(RecordedRange(0, 10) + 5);
        SetPolarVelocity(field314, 100.0f);
        SpawnBattleEffect(0x38F,
            (g_ReimuStormPairXBaseAt00658264 + velocityX) * static_cast<float>(facing) + x,
            (y + g_ReimuFallingSpawnYOffsetAt0065908C) - velocityY, facing, 1);
        velocityX = static_cast<float>(scriptCounterF00) * g_ReimuStormFallAt00658044;
        velocityY = static_cast<float>(scriptCounterF02) * g_ReimuStormFallAt00658044;
        PlaySound(7);
    }
    if (animationStage == 0x17 && animationFrame == 0 &&
        fieldF04 < g_ReimuRepeatSettingAt006714D0 * 2 + 8) {
        ++fieldF04;
        ResetSecondaryCounter(0x0F);
    }
    if (animationStage == 0x22 && animationFrame == 0) ResetSecondaryCounter(0x20);
    return;
}
