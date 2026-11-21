// Reimu Fighter::Advance native action 0x19F at 0045DD70.
// Five-shot cadence driven by the signed 16-bit delay/counter pair; the
// secondary counter reset precedes each 40-point gauge timer update.
case 0x19F:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        velocityX = velocityX * g_BounceScaleAt00657F74;
        velocityY = velocityY * g_BounceScaleAt00657F74;
    }
    if (animationStage > 4 && scriptCounterF00 < 1 && scriptCounterF02 < 5) {
        ResetSecondaryCounter(0);
        UpdateGaugeTimer(0x28);
        field314 = static_cast<float>(scriptCounterF02 * -4 - 0x2D);
        field318 = 15.0f;
        SpawnBattleEffect(0x326, x, y + g_ReimuCommandFrontYAt006590AC,
            facing, 1);
        scriptCounterF00 = 2;
        ++scriptCounterF02;
    }
    --scriptCounterF00;
    if (y + velocityY < g_ThresholdAt0065782C) {
        y = 0.0f;
        ClearMotionFields();
        ResetPrimaryCounters(10);
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(9);
    }
    if (animationStage == 4 && animationFrame == 0) {
        SpawnBattleEffect(0x335, x, y, facing, 1);
    }
    return;
