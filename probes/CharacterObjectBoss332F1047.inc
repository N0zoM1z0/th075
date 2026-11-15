// Original 0050D88E..0050D929: real action 0x332 (155B/35 x86).
case 0x332: {
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        ResetTransform(0,0,0);
        scaleX = 1.0f;
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
