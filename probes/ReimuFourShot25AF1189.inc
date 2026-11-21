// Reimu Fighter::Advance native action 0x25A.
// Four 0x321 projectiles after the quarter-speed opening and stage-3 transition.
case 0x25A:
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
    field314 = 0.0f;
    field318 = y + g_ReimuCommandBackYAt006590A8;
    SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 1.0f;
    SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 2.0f;
    SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 3.0f;
    SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    UpdateGaugeTimer(0xFA);
    ResetSecondaryCounter(4);
    return;
