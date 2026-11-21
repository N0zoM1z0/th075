// Reimu Fighter::Advance native action 0x25D.
// Six 0x320 shots at stage 6 with the original nonuniform angle fan.
case 0x25D:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
    }
    if (animationStage == 6 && animationFrame == 0) {
        field314 = 20.0f;
        field318 = 10.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        field314 = 40.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        field314 = 70.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        field314 = -20.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        field314 = -40.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        field314 = -70.0f;
        SpawnBattleEffect(0x320, x + static_cast<float>(facing * 0x1E),
            y + g_ReimuSpecialYAt0065908C, facing, 1);
        UpdateGaugeTimer(0xFA);
        PlaySound(5);
    }
    if (AdvanceNestedFrame() != animationStageCount) {
        return;
    }
    ResetPrimaryCounters(0);
    return;
