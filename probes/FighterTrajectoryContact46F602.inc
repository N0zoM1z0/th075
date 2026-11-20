// F602: original fighter second-switch state 0x46 movement, projectile
// handoff and x87-to-short motion conversion. These are internal native
// actions inside still-nonexact giant Advance() owners, NOT independent
// executable functions. The owning original may use different stage
// thresholds, event parameters and counters (validated separately).
case 0x46: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -(field094);
        velocityY += field098;
        if (velocityY < TRAJECTORY_LOWER_THRESHOLD)
            velocityY = TRAJECTORY_MINIMUM_SPEED;
        field05C = 0.8f;
        if (velocityY > TRAJECTORY_UPPER_THRESHOLD)
            velocityY = TRAJECTORY_MAXIMUM_SPEED;
        field07C = 0;
    }
    if (animationStage == TRAJECTORY_STAGE_THRESHOLD && velocityY < g_StopThresholdAt00657480) {
        ResetSecondaryCounter(TRAJECTORY_EARLY_STATE);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(TRAJECTORY_LATE_STATE);
    break;
}
