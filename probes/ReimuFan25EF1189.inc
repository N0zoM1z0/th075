// Reimu Fighter::Advance native action 0x25E.
case 0x25E:
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
    field314 = -28.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -21.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -14.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = -7.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 0.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 7.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 14.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 21.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    field314 = 28.0f;
    field318 = 10.0f;
    SpawnBattleEffect(0x342, x,
        y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    return;
