// F1046: Original 0050AC27..0050AD46 action 0x322, 287 native CODE
// bytes / 56 x86. True game behavior, NOT an independent callable.
case 0x322: {
    if (field07C == 5) {
        ClearFrameInfo();
        return;
    }
    if (field07C == 6) {
        field07C = 0;
        field080 = 1;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0,0,0);
        field080 = 1;
        field07C = 0;
        field0D8 = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationZ = 15.0f;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;
}
