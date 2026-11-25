// Reimu Fighter::Advance native action 0x25E.
// Quarter-speed opening followed by the two-shot 0x320 stage-3 fan.
case 0x25E:
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = (velocityX) * FloatConstants::Quarter;
        velocityY = (velocityY) * FloatConstants::Quarter;
        collisionResult = 1;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(9);
    }
    if (animationStage == 3 && animationFrame == 0) {
        field314 = -30.0f;
        field318 = 10.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
            (y) + GeometryConstants::HundredTwenty, facing, 1);
        field314 = 30.0f;
        field318 = 10.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
            (y) + GeometryConstants::HundredTwenty, facing, 1);
        UpdateGaugeTimer(100);
        PlaySound(5);
    }
    return;
