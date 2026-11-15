// F1054: Real native action 0x345, original 155B/35 x86; one 81KB parent.
case 0x345: {
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        ResetTransform(0,0,0);
        scaleX = 2.0f;
        scaleY = 2.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if (AdvanceNestedFrame() == field070)
        ClearFrameInfo();
    return;
}
