// F602: original fighter second-switch state 0x46 movement, projectile
// handoff and x87-to-short motion conversion. These are internal native
// actions inside still-nonexact giant Advance() owners, NOT independent
// executable functions. The owning original may use different stage
// thresholds, event parameters and counters (validated separately).
case 0x46: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -(hitReactionVelocityX);
        velocityY += hitReactionVelocityY;
        if (velocityY < TRAJECTORY_LOWER_THRESHOLD)
            velocityY = TRAJECTORY_MINIMUM_SPEED;
        field05C = 0.8f;
        if (velocityY > TRAJECTORY_UPPER_THRESHOLD)
            velocityY = TRAJECTORY_MAXIMUM_SPEED;
        field07C = 0;
    }
    if (animationStage == TRAJECTORY_STAGE_THRESHOLD && velocityY < FloatConstants::Two) {
        ResetSecondaryCounter(TRAJECTORY_EARLY_STATE);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
        scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
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
