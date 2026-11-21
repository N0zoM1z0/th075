// Reimu Fighter::Advance native action 0x25F.
// Quarter-speed opening followed by the six-shot 0x320 stage-3 fan.
case 0x25F:
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = velocityX * g_BounceScaleAt00657F74;
        velocityY = velocityY * g_BounceScaleAt00657F74;
        field07C = 1;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(9);
    }
    if (animationStage != 3 || animationFrame != 0) {
        return;
    }
    field314 = 20.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 40.0f;
    SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 60.0f;
    SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = -20.0f;
    SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = -40.0f;
    SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = -60.0f;
    SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    UpdateGaugeTimer(0xFA);
    ResetSecondaryCounter(5);
    return;
