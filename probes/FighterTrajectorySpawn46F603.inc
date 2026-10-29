// F603: real 131-instruction fighter action0x46 in two original giants.
// Native stage-one projectile ownership is in addition to the genuine
// 104-instruction F602 trajectory; these remain original whole-fighter
// internal case source, NOT independent/accepted exact game CODE.
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
    // Native 131-instruction owners alone have this real one-shot
    // stage-one projectile branch (+0xF0C is the original flag).
    if (I16(0x62) == 1 && I16(0x64) == 0 && I16(0xF0C) == 0) {
        I16(0xF0C) = 1;
        SpawnDirectedAt453A70(TRAJECTORY_SPAWN_KIND,
            I32(0x44), I32(0x48),
            *reinterpret_cast<signed char*>(RAW + 0x66), TRAJECTORY_SPAWN_SIDE);
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
