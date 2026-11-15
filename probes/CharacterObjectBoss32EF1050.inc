// Pinned original native 0050CF7A..0050D097, action 0x32E, 285B/63 x86.
// This remains an INNER state in one nonexact 81KB CharacterObject function.
case 0x32E: {
    reinterpret_cast<unsigned char&>(facing) = reinterpret_cast<unsigned char&>(owner->facing);
    if (owner->action == 0x131) {
        reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
        reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
    } else {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62 == 0 &&
        F1024_PHASE(this).frameAt64 == 0 &&
        field0D8 == 0) {
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
