// Reimu Fighter::Advance native action 0x25A.
// Five fixed-angle 0x325 shots at stage 5, followed by the 250-point gauge update.
case 0x25A:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
    }
    if (animationStage != 5 || animationFrame != 0) {
        return;
    }
    ResetSecondaryCounter(0);
    field314 = 10.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x325, x + static_cast<float>(facing * 0x61),
        y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
    field314 = 5.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x325, x + static_cast<float>(facing * 0x61),
        y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
    field314 = 0.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x325, x + static_cast<float>(facing * 0x61),
        y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
    field314 = 5.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x325, x + static_cast<float>(facing * 0x61),
        y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
    field314 = 10.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x325, x + static_cast<float>(facing * 0x61),
        y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
    UpdateGaugeTimer(0xFA);
    return;
