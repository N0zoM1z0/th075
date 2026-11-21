// Reimu Fighter::Advance native action 0x25C.
case 0x25C:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(0);
    if (animationStage != 6 || animationFrame != 0) return;
    ResetSecondaryCounter(0);
    UpdateGaugeTimer(0xFA);
    field314 = -28.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -21.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -14.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -7.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 0.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 7.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 14.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 21.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 28.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    return;
