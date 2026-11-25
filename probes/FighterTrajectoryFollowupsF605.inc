// F605: native second packed-switch actions 0x47 and 0x48 in large
// original fighter Advance() functions. These are NOT independent
// function credits; owner-specific spawn variants differ.
case 0x47: {
    // Original copying +0x98 to +0x54 is MOV dword, not FLD/FSTP.
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(hitReactionVelocityX);
        velocityY = hitReactionVelocityY;
        verticalAcceleration = 0.8f;
        collisionResult = 0;
    }
    if (animationStage==F605_STAGE47 && velocityY < FloatConstants::Two) {
        ResetSecondaryCounter(F605_EARLY47);
        break;
    }
    velocityY = velocityY - verticalAcceleration;
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
        scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(F605_LATE47);
    break;
}
case 0x48: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(hitReactionVelocityX);
        velocityY = hitReactionVelocityY;
        verticalAcceleration = 1.3f;
        collisionResult = 0;
    }
    if (animationStage==F605_STAGE48 && velocityY < FloatConstants::Two) {
        ResetSecondaryCounter(F605_EARLY48);
        break;
    }
    velocityY = velocityY - verticalAcceleration;
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
        scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(F605_LATE48);
    break;
}
