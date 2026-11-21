// Reimu Fighter::Advance native action 0x262.
case 0x262:
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
    for (int shot = 0; shot < 10; ++shot) {
        field314 = static_cast<float>(shot * -6 + 0x1E);
        field318 = 15.0f;
        SpawnBattleEffect(0x347, x,
            y + g_ReimuCommandFrontYAt006590AC, facing, 1);
    }
    return;
