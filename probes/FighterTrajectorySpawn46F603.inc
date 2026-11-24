// F603: real 131-instruction fighter action0x46 in two original giants.
// Native stage-one projectile ownership is in addition to the genuine
// 104-instruction F602 trajectory; these remain original whole-fighter
// internal case source, NOT independent/accepted exact game CODE.
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
    // Native 131-instruction owners alone have this real one-shot
    // stage-one projectile branch (+0xF0C is the original flag).
    if (animationStage == 1 && animationFrame == 0 && fieldF0C == 0) {
        fieldF0C = 1;
        SpawnBattleEffect(TRAJECTORY_SPAWN_KIND,x,y,
            facing, TRAJECTORY_SPAWN_SIDE);
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
