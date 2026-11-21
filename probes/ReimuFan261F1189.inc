// Reimu Fighter::Advance native action 0x261.
case 0x261:
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
    UpdateGaugeTimer(0x96);
    field314 = 30.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 24.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 18.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 12.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 6.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 0.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -6.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -12.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -18.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -24.0f;
    field318 = 15.0f;
    SpawnBattleEffect(0x346, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    return;
