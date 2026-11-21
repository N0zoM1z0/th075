// Reimu Fighter::Advance native action 0x60 at 0045DD70.
// Input direction selects the launch; stage-0 children, strict ground
// crossing, and the field3CF-dependent completion tail follow the PE CFG.
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
        for (int shot = 0; shot < 10; ++shot) {
            SpawnBattleEffect(0x3E4, x, y, 1, 1);
        }
        if (fieldEFA > 25) {
            fieldEFA = 0;
            SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
    }
    if (animationStage > 2 && animationStage < 6) {
        velocityY = velocityY - field05C;
        if (y + velocityY < g_ThresholdAt0065782C) {
            y = 0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(6);
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0x62);
        if (field3CF == 0) {
            ResetPrimaryCounters(99);
        }
        return;
    }
    if (animationStage != 3 || animationFrame != 0) {
        return;
    }
    velocityX = static_cast<float>(scriptCounterF00) * g_ReimuRecoveryScaleAt006590B8;
    velocityY = static_cast<float>(-scriptCounterF02) * g_ReimuRecoveryScaleAt006590B8;
    field05C = 2.0f;
    return;
