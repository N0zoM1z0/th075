// Native 0050A658..0050A80F (439 original CODE B, 91 x86) is action 0x320
// of the ONE, still NONEXACT 81KB CharacterObject Advance. This body is a
// natural C++ source reconstruction, not separately callable CODE or ASM.
case 0x320: {
    // The actual original parent chain is this+E4. Its native action and
    // stage fields gate a real helper call before any local motion update.
    if (owner->action != 0x2BC ||
        (owner->action == 0x2BC &&
         owner->animationStage > 12)) {
        ClearFrameInfo();
        return;
    }
    x = F1037_POSITION(PARENT).xPosition + float(facing * 66);
    if (F1024_PHASE(this).stageAt62 == 0 &&
        F1024_PHASE(this).frameAt64 == 0) {
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
        velocityY = 10.0f;
    }
    F1037_POSITION(this).yPosition = F1037_POSITION(this).yPosition + F1037_MOTION(this).yMotion;
    velocityY = (velocityY) - g_F1044_GravityAt0065747C;
    if (velocityY < g_F1044_GroundAt0065782C)
        velocityY = 0.0f;
    if (AdvanceNestedFrame() == field070)
        ResetSecondaryCounter(1);
    return;
}
