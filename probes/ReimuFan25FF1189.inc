// Reimu Fighter::Advance native action 0x25F.
case 0x25F:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(0);
    if (animationStage != 6 || animationFrame != 0) return;
    if (scriptCounterF00 > 0 || scriptCounterF02 > 0) return;
    ResetSecondaryCounter(0);
    UpdateGaugeTimer(0x96);
    field314 = 30.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 24.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 18.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 12.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 6.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = 0.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -6.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -12.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -18.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    field314 = -24.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x + static_cast<float>(facing * 0x31),
        y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
    velocityX = static_cast<float>(scriptCounterF00) * g_ReimuStormFallAt00658044;
    velocityY = static_cast<float>(scriptCounterF02) * g_ReimuStormFallAt00658044;
    scriptCounterF00 = 2;
    ++scriptCounterF02;
    return;
