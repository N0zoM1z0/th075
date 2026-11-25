// F610 original native fighter second-switch action 0x4A inside whole
// incomplete giant Advance() C++ source; not an independent function.
case 0x4A: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(hitReactionVelocityX);
        velocityY = hitReactionVelocityY;
        field05C = 0.8f;
        collisionResult = 0;
    }
    if (animationStage==F610_STAGE && velocityY < FloatConstants::Two) {
        ResetSecondaryCounter(F610_EARLY);
        break;
    }
    if (CheckHorizontalLimits() && (velocityX) <= GeometryConstants::NegativeFifteen) {
        ResetPrimaryCounters(0x4C);
        velocityX = -(velocityX) * FloatConstants::Quarter;
        velocityY = 15.0f;
        field05C = 0.5f;
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        scriptCounterF00 = 0;
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= FloatConstants::Zero) {
#if F610_PREPARE_BEFORE
        PlaySharedSound(0x16);
#endif
        scriptCounterF00=static_cast<short>((velocityX) * GeometryConstants::Hundred);
        scriptCounterF02=static_cast<short>((velocityY) * GeometryConstants::Hundred);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
#if !F610_PREPARE_BEFORE
        PlaySharedSound(0x16);
#endif
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(F610_LATE);
    break;
}
