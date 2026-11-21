// Reimu Fighter::Advance native action 0x25C.
// Two opposite 0x320 shots at stage 6, then the native 100-point gauge/reset-5 tail.
case 0x25C:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
    }
    if (animationStage == 6 && animationFrame == 0) {
        field314 = 30.0f;
        field318 = 10.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        field314 = -30.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        UpdateGaugeTimer(100);
        ResetSecondaryCounter(5);
    }
    if (AdvanceNestedFrame() != animationStageCount) {
        return;
    }
    ResetPrimaryCounters(0);
    return;
