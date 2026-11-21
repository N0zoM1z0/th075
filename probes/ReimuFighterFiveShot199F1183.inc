// Reimu Fighter::Advance native action 0x199 at 0045DD70.
// Quarter-speed opening, five stepped 0x328 projectiles, and the 150-point
// gauge update follow the original stage-5 firing sequence.
case 0x199:
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = velocityX * 0.25f;
        velocityY = velocityY * 0.25f;
        field07C = 1;
    }
    if (y + velocityY <= g_ThresholdAt0065782C) {
        y = 0.0f;
        ClearMotionFields();
        ResetPrimaryCounters(10);
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 5 && animationFrame == 0) {
        PlaySound(0);
        field314 = 0.0f;
        field318 = 20.0f;
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 76), y + 136.0f, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 81), y + 122.0f, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 86), y + 107.0f, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 91), y + 92.0f, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 96), y + 77.0f, facing, 1);
        UpdateGaugeTimer(0x96);
    }
    return;
