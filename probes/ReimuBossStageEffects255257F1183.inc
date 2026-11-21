// Reimu Fighter::Advance native actions 0x255, 0x256 and 0x257.
// Shared auxiliary-effect lifecycle; 255 alone plays the global sound and
// 255/257 alone perform the one-shot stage-8 restart.
case 0x255:
case 0x256:
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
        SpawnAuxEffect(0x37, x,
            y + g_ContactProjectionAt00657888, facing, 1);
        if (action == 0x255) PlaySharedSound(0x21);
    }
    if (action != 0x256 && animationStage == 8 && animationFrame == 0 &&
        scriptCounterF00 <= 0) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    return;
