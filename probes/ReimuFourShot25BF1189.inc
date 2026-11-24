// Reimu Fighter::Advance native action 0x25B.
// Four ordered 0x322 projectiles at stage 3, then the native gauge/sound tail.
case 0x25B:
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = (velocityX) * FloatConstants::Quarter;
        velocityY = (velocityY) * FloatConstants::Quarter;
        field07C = 1;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(9);
    if (animationStage == 3 && animationFrame == 0) {
        field314 = 0.0f;
        field318 = (y) + GeometryConstants::HundredTwenty;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
            (y) + GeometryConstants::HundredTwenty, facing, 1);
        field314 = 1.0f;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
            (y) + GeometryConstants::HundredTwenty, facing, 1);
        field314 = 2.0f;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
            (y) + GeometryConstants::HundredTwenty, facing, 1);
        field314 = 3.0f;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
            (y) + GeometryConstants::HundredTwenty, facing, 1);
        UpdateGaugeTimer(0xFA);
        PlaySound(4);
    }
    return;
