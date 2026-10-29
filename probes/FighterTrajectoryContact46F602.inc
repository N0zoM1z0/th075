// F602: original fighter second-switch state 0x46 movement, projectile
// handoff and x87-to-short motion conversion. These are internal native
// actions inside still-nonexact giant Advance() owners, NOT independent
// executable functions. The owning original may use different stage
// thresholds, event parameters and counters (validated separately).
case 0x46: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -F32(0x94);
        POS54 = *(&POS54) + *(&F32(0x98));
        if (POS54 < TRAJECTORY_LOWER_THRESHOLD)
            POS54 = TRAJECTORY_MINIMUM_SPEED;
        POS5C = 0.8f;
        if (POS54 > TRAJECTORY_UPPER_THRESHOLD)
            POS54 = TRAJECTORY_MAXIMUM_SPEED;
        I32(0x7C) = 0;
    }
    if (I16(0x62) == TRAJECTORY_STAGE_THRESHOLD && POS54 < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(TRAJECTORY_EARLY_STATE);
        break;
    }
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(CONTACT_STAGE_OFFSET) = static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(CONTACT_STAGE_OFFSET + 2) = static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48 = 0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetAuxActionAt40FB40(TRAJECTORY_LATE_STATE);
    break;
}
