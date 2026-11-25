// F961 real original Japanese 004AC040 stages 12F/130.
 // 12F: 004B12F1..004B13C0, 207 CODE B /59 x86 /6 original PE fields.
 // 130: 004B13C0..004B14C9, 265 CODE B /81 x86 /6 original PE fields.
 // Both are native GPR/mnemonic/width-complete INTERNAL cases,
 // not separate whole game functions; parent 82KB remains NONEXACT.
// Genuine original 004AC040 12F: native 207B/59x86.
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
