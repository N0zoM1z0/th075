// F603: real 131-instruction fighter action0x46 in two original giants.
// Native stage-one projectile ownership is in addition to the genuine
// 104-instruction F602 trajectory; these remain original whole-fighter
// internal case source, NOT independent/accepted exact game CODE.
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
    // Native 131-instruction owners alone have this real one-shot
    // stage-one projectile branch (+0xF0C is the original flag).
    if (animationStage == 1 && animationFrame == 0 && fieldF0C == 0) {
        fieldF0C = 1;
        SpawnDirectedAt453A70(TRAJECTORY_SPAWN_KIND,
            reinterpret_cast<int&>(x), reinterpret_cast<int&>(y),
            facing, TRAJECTORY_SPAWN_SIDE);
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
