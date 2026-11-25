// F598: real original fighter singleton 0x32/50, not a standalone function.
// Included inside the native 11-case switch; entire parent fighter remains
// an incomplete diagnostic C++ probe until all later actions are rebuilt.
case 0x32: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -8.0f;
        velocityY = 0.0f;
        collisionResult = 0;
    }
    if ((velocityX) < FloatConstants::Zero) {
        velocityX = (velocityX) + FloatConstants::ThreeFifths;
        if ((velocityX) > FloatConstants::Zero)
            velocityX = 0.0f;
    }
    if (CheckHorizontalLimits() &&
        field3BE) {
        opponentVelocityDeltaX =
            static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(0);
    break;
}
