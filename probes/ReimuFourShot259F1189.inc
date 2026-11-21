// Reimu Fighter::Advance native action 0x259.
// Four ordered 0x322 projectiles at stage 8; this sibling differs by effect ID.
case 0x259:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
    }
    if (animationStage != 8 || animationFrame != 0) {
        return;
    }
    field314 = 0.0f;
    field318 = y + g_ReimuLowVolleyYAt006590A0;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
        y + g_ReimuLowVolleyYAt006590A0, facing, 1);
    field314 = 1.0f;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
        y + g_ReimuLowVolleyYAt006590A0, facing, 1);
    field314 = 2.0f;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
        y + g_ReimuLowVolleyYAt006590A0, facing, 1);
    field314 = 3.0f;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
        y + g_ReimuLowVolleyYAt006590A0, facing, 1);
    UpdateGaugeTimer(0xFA);
    ResetSecondaryCounter(4);
    return;
