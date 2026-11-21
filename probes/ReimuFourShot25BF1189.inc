// Reimu Fighter::Advance native action 0x25B.
// Four ordered 0x322 projectiles at stage 3, then the native gauge/sound tail.
case 0x25B:
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = velocityX * g_BounceScaleAt00657F74;
        velocityY = velocityY * g_BounceScaleAt00657F74;
        field07C = 1;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(9);
    if (animationStage != 3 || animationFrame != 0)
        return;
    field314 = 0.0f;
    field318 = y + g_ReimuCommandBackYAt006590A8;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 1.0f;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 2.0f;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    field314 = 3.0f;
    SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x0C),
        y + g_ReimuCommandBackYAt006590A8, facing, 1);
    UpdateGaugeTimer(0xFA);
    PlaySound(4);
    return;
