// F629: genuine complete original native action0x91 arc trajectory,
// inside a huge incomplete fighter Advance(). Game case evidence,
// not an independent original CODE function or accepted match unit.
case 0x91: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=-10.0f;
        velocityY=14.0f;
        verticalAcceleration=0.5f;
        collisionResult=0;
    }
    if (animationStage==F629_STAGE && velocityY<FloatConstants::Two) {
        ResetSecondaryCounter(F629_EARLY);
        break;
    }
    velocityY=velocityY-verticalAcceleration;
    if (velocityY+y<=FloatConstants::Zero) {
        scriptCounterF00=static_cast<short>((velocityX)*GeometryConstants::Hundred);
        scriptCounterF02=static_cast<short>((velocityY)*GeometryConstants::Hundred);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(F629_LATE);
    break;
}
