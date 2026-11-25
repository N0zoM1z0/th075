// Original 0050CCC3..0050CD7A: one actual action 0x32B (183B/39 x86).
case 0x32B: {
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0,0,0);
        remainingHits = 1;
        collisionResult = 0;
        scaleX = 2.0f;
        scaleY = 2.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;
}
