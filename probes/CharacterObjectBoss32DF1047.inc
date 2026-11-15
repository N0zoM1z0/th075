// Original 0050CE97..0050CF7A: real action 0x32D (227B/50 x86).
case 0x32D: {
    if (owner->action == 0x12D) {
        reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
        reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0,0,0);
        scaleX = 1.5f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if (AdvanceNestedFrame() == field070)
        ClearFrameInfo();
    return;
}
