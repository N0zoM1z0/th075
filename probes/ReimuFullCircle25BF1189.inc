// Reimu Fighter::Advance native action 0x25B at 0045DD70.
// Full-circle 0x327 ring: the native handler emits 36 individually ordered
// projectiles and keeps the short countdown / one-shot guard around the burst.
case 0x25B: {
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
    }
    --scriptCounterF00;
    if (animationStage > 5 && scriptCounterF00 < 1 && scriptCounterF02 < 1) {
        ResetSecondaryCounter(0);
        UpdateGaugeTimer(0xFA);
        field314 = 0.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 10.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 20.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 30.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 40.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 50.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 60.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 70.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 80.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 90.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 100.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 110.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 120.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 130.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 140.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 150.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 160.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 170.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 180.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 190.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 200.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 210.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 220.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 230.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 240.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 250.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 260.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 270.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 280.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 290.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 300.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 310.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 320.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 330.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 340.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        field314 = 350.0f;
        field318 = 7.0f;
        SpawnBattleEffect(0x327,
            static_cast<float>(facing * 0x31) + x,
            y + g_ReimuFullCircleYOffsetAt00659294, facing, 1);
        scriptCounterF00 = 2;
        ++scriptCounterF02;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
    }
    return;
}
