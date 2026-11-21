// Reimu Fighter::Advance native action 0x60 at 0045DD70.
// Direction/button capture, the ten-shot opening, the fieldEFA bonus shot,
// and the stage-3 launch/landing transition are restored as C++.
case 0x60:
    if (static_cast<int>(facing) * inputX > 0 &&
        (inputA != 0 || inputB != 0 || inputC != 0 || inputD != 0)) {
        scriptCounterF00 = 1;
    }
    if (static_cast<int>(facing) * inputX < 0 &&
        (inputA != 0 || inputB != 0 || inputC != 0 || inputD != 0)) {
        scriptCounterF00 = 2;
    }
    if (animationStage == 0 && animationFrame == 0) {
        for (int shot = 0; shot < 10; ++shot) SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if (fieldEFA > 0x19) {
            fieldEFA = 0;
            SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
    }
    if (animationStage > 2 && animationStage < 6) {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            y = 0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(6);
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0x62);
        if (field3CF != 0) return;
        ResetPrimaryCounters(99);
        return;
    }
    if (animationStage == 3 && animationFrame == 0) {
        velocityX = static_cast<float>(scriptCounterF00) * 0.005f;
        velocityY = static_cast<float>(-scriptCounterF02) * 0.005f;
        field05C = 2.0f;
    }
    return;
