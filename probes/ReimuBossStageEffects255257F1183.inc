// Reimu Fighter::Advance native action 0x255.
// Stage-5 auxiliary effect and shared sound; stage-8 one-shot restart.
case 0x255:
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        field080 = 1;
        field07C = 0;
        field3AC = 0;
        scriptCounterF00 = 0;
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 5 && animationFrame == 0) {
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        PlaySharedSound(0x21);
    }
    if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 <= 0) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    return;

// Reimu Fighter::Advance native action 0x256.
// This sibling only emits the stage-5 auxiliary effect.
case 0x256:
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        field080 = 1;
        field07C = 0;
        field3AC = 0;
        scriptCounterF00 = 0;
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 5 && animationFrame == 0) {
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
    }
    return;

// Reimu Fighter::Advance native action 0x257.
// Same one-shot stage-8 restart as 0x255, without the shared sound.
case 0x257:
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        field080 = 1;
        field07C = 0;
        field3AC = 0;
        scriptCounterF00 = 0;
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 5 && animationFrame == 0) {
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
    }
    if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 <= 0) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    return;
