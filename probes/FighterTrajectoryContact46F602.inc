// F602: original fighter second-switch state 0x46 movement, projectile
// handoff and x87-to-short motion conversion. These are internal native
// actions inside still-nonexact giant Advance() owners, NOT independent
// executable functions. The owning original may use different stage
// thresholds, event parameters and counters (validated separately).
case 0x46: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        velocityY = *(&velocityY) + *(&reinterpret_cast<float&>(field098));
        if (velocityY < TRAJECTORY_LOWER_THRESHOLD)
            velocityY = TRAJECTORY_MINIMUM_SPEED;
        field05C = 0.8f;
        if (velocityY > TRAJECTORY_UPPER_THRESHOLD)
            velocityY = TRAJECTORY_MAXIMUM_SPEED;
        field07C = 0;
    }
    if (animationStage == TRAJECTORY_STAGE_THRESHOLD && velocityY < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(TRAJECTORY_EARLY_STATE);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(CONTACT_STAGE_OFFSET) = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(CONTACT_STAGE_OFFSET + 2) = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y = 0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30() == field070)
        SetAuxActionAt40FB40(TRAJECTORY_LATE_STATE);
    break;
}
