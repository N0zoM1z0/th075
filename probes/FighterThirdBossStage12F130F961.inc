// Sakuya actions 0x12F and 0x130 start at 0x004B12F1 and 0x004B13C0.
case 0x12F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
            ClearMotionFields();
                    remainingHits=1;
        collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(2);
    if ((animationStage)==4 && (animationFrame)==0)
        PlaySharedSound(0x1C);
    break;
}
// Genuine original 004AC040 130: native 265B/81 x86, original sprite334.
case 0x130: {
    velocityY=velocityY-verticalAcceleration;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(0xA);
        y=0.0f;
        verticalAcceleration=0.0f;
        velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==3 && (animationFrame)==0)
        PlaySharedSound(0x1C);
    if ((animationStage)==3 && (animationFrame)==0) {
        Fighter::SpawnTrackedEffect(0x334,x,y,
            facing,1,0,1);
    }
    else if (animationStage == 3 && animationFrame != 0) {
        // Continue the stage after the opening shot.
    }
    break;
}
