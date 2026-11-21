// Reimu Fighter::Advance native action 0x2FA at 0045DD70.
// Timed 0x38E launches, difficulty-adjusted cooldown and stage-2 horizontal
// reversal preserve the original trajectory controller.
case 0x2FA: {
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        fieldF04 = 0;
        fieldF06 = 0;
        fieldF08 = static_cast<short>(g_ReimuRepeatSettingAt006714D0 + 2);
    }
    if (g_ThresholdAt0065782C < y) {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetSecondaryCounter(0x0F);
            ClearMotionFields();
            y = 0.0f;
            return;
        }
    }
    ++scriptCounterF00;
    if (animationStage > 3 && animationStage < 0x0B && scriptCounterF00 > 8) {
        scriptCounterF00 = 0;
        field314 = -45.0f;
        SpawnBattleEffect(0x38E, x, y + g_ContactProjectionAt00657888, facing, 1);
        PlaySound(0x0C);
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        aiCardTimer = static_cast<short>(RecordedRange(60, 120) -
            g_ReimuRepeatSettingAt006714D0 * 20);
    }
    if (animationStage == 2 && animationFrame == 0) {
        velocityY = 16.0f;
        field05C = 0.5f;
        velocityX = static_cast<float>(RecordedRange(0, 6) + 0x0C);
        if ((facing == 1 && g_ReimuApproachRightBoundAt0065945C < x) ||
            (facing == -1 && x < g_ContactProjectionAt00657888)) {
            velocityX = -velocityX;
        }
    }
    if (animationStage == 0x0B && animationFrame == 0 && scriptCounterF02 < 1) {
        ++scriptCounterF02;
        ResetSecondaryCounter(4);
    }
    if (animationStage == 0x0F && animationFrame == 0) ResetSecondaryCounter(0x0D);
    return;
}
