// Reimu Fighter::Advance native action 0x19F at 0045DD70.
// A five-shot cadence driven by the signed 16-bit delay/counter pair, followed
// by the stage-4 0x335 effect.
case 0x19F:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
        velocityX = velocityX * 0.25f;
        velocityY = velocityY * 0.25f;
    }
    if (animationStage > 4 && scriptCounterF00 < 1 && scriptCounterF02 < 5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314 = static_cast<float>(-45 - scriptCounterF02 * 4);
        field318 = 15.0f;
        SpawnBattleEffect(0x326, x, y + 110.0f, facing, 1);
        scriptCounterF00 = 2;
        ++scriptCounterF02;
    }
    --scriptCounterF00;
    if (y + velocityY <= g_ThresholdAt0065782C) {
        y = 0.0f;
        ClearMotionFields();
        ResetPrimaryCounters(10);
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 4 && animationFrame == 0) SpawnBattleEffect(0x335, x, y, facing, 1);
    return;
