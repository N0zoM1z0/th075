// F606: real original 113-instruction second-switch case 0x47 or 0x48
// in the two extended fighter giants. Caller declares the true case,
// original drag, projectile kind, one-shot side and stage policy.
// Each inclusion is a naturally-typed C++ case inside whole Advance().
// These are NOT independently callable or accepted whole functions.
case F606_ACTION: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(hitReactionVelocityX);
        velocityY = hitReactionVelocityY;
        verticalAcceleration = F606_DRAG;
        collisionResult = 0;
    }
    if (animationStage==1 && animationFrame==0 && fieldF0C==0) {
        fieldF0C=1;
        SpawnBattleEffect(F606_PROJECTILE,x,y,
            facing, F606_SIDE);
    }
    if (animationStage==F606_STAGE && velocityY<FloatConstants::Two) {
        ResetSecondaryCounter(F606_EARLY);
        break;
    }
    velocityY = velocityY - verticalAcceleration;
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00=static_cast<short>((velocityX) * GeometryConstants::Hundred);
        scriptCounterF02=static_cast<short>((velocityY) * GeometryConstants::Hundred);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(F606_LATE);
    break;
}
