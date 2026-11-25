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
    x = owner->x + float(facing * 66);
    if (animationStage == 0 &&
        animationFrame == 0) {
        ResetTransform(0,0,0);
        remainingHits = 1;
        collisionResult = 0;
        field0D8 = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        velocityY = 10.0f;
    }
    y = y + velocityY;
    velocityY = (velocityY) - FloatConstants::One;
    if (velocityY < FloatConstants::Zero)
        velocityY = 0.0f;
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(1);
    return;
}
