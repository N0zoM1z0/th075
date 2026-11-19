// Pinned original native 0050CD7A..0050CE97, action 0x32C, 285B/63 x86.
// This remains an INNER state in one nonexact 81KB CharacterObject function.
case 0x32C: {
    facing = owner->facing;
    if (owner->action == 0x131) {
        x = owner->x;
        y = owner->y;
    } else {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 &&
        animationFrame == 0 &&
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
