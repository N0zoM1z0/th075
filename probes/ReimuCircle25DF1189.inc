// Reimu Fighter::Advance native action 0x25D.
case 0x25D:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        velocityX = velocityX * g_BounceScaleAt00657F74;
        velocityY = velocityY * g_BounceScaleAt00657F74;
    }
    if (animationStage > 4) velocityY = velocityY - field05C;
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage != 4 || animationFrame != 0) return;
    velocityX = -3.0f;
    velocityY = 9.0f;
    field05C = 0.7f;
    ResetSecondaryCounter(0);
    UpdateGaugeTimer(0xFA);
    field314 = 0.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 10.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 20.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 30.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 40.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 50.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 60.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 70.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 80.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 90.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 100.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 110.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 120.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 130.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 140.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 150.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 160.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 170.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 180.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 190.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 200.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 210.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 220.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 230.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 240.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 250.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 260.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 270.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 280.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 290.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 300.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 310.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 320.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 330.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 340.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 350.0f;
    field318 = 7.0f;
    SpawnBattleEffect(0x327, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    return;
