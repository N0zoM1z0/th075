// Reimu Fighter::Advance native action 0x199 at 0045DD70.
// Quarter-speed opening, five stepped 0x328 projectiles, and the 150-point
// gauge update follow the original stage-5 firing sequence.
case 0x199:
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = velocityX * g_BounceScaleAt00657F74;
        velocityY = velocityY * g_BounceScaleAt00657F74;
        field07C = 1;
    }
    if (y + velocityY < g_ThresholdAt0065782C) {
        y = 0.0f;
        ClearMotionFields();
        ResetPrimaryCounters(10);
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(9);
    }
    if (animationStage == 5 && animationFrame == 0) {
        ResetSecondaryCounter(0);
        field314 = 0.0f;
        field318 = 20.0f;
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 0x4C),
            y + g_ReimuStormRingYOffsetAt0065836C, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 0x51),
            y + g_ReimuFiveShotSecondYAt00659474, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 0x56),
            y + g_ReimuFiveShotThirdYAt00657860, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 0x5B),
            y + g_ReimuFiveShotFourthYAt00659284, facing, 1);
        SpawnBattleEffect(0x328, x + static_cast<float>(facing * 0x60),
            y + g_ReimuFiveShotFifthYAt00659470, facing, 1);
        UpdateGaugeTimer(0x96);
    }
    return;
