// F646 original native D0: reverse facing and x87 horizontal
// reflection, native conditional ground physics and aux-state exit.
// This is an original interior case, not an accepted entire giant.
case 0xD0: {
    if (animationStage==0 && animationFrame==0) {
        facing =
            -facing;
        velocityX=-(velocityX);
    }
    if (*(&verticalAcceleration)==FloatConstants::Zero)
        verticalAcceleration=0.6f;
    velocityY=velocityY-verticalAcceleration;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(0xA);
        y=0.0f;
        ClearMotionFields();
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(5);
    break;
}
