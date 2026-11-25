// F963: original pinned Japanese TH075 004AC040 action 133 & 134.
 // 133 physically 004B1593..004B16AD 282 B/84 x86/7 typed PE fields;
 // 134 physically 004B16AD..004B18B1 516 B/152 x86/12 PE fields.
 // Natural C++ preserves all original mnemonic and width ordinals.
 // 53/98 GPR roles differ in still PARTIAL/nonexact 82KB father.
// F963 original 004AC040 stage133 native evidence, partial giant.
case 0x133: {
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
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        scriptCounterF00=0;
    }
    if ((animationStage)==4 && (animationFrame)==0)
        PlaySharedSound(0x1C);
    if ((animationStage)==3 && (animationFrame)==0)
        Fighter::SpawnTrackedEffect(0x324,x,y,
            facing,1,0,1);
    break;
}
// F963 original 004AC040 stage134 native evidence, partial giant.
case 0x134: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        verticalAcceleration=0.0f;
        remainingHits=1;
        collisionResult=0;
    }
    if ((velocityX)>FloatConstants::Zero)
        velocityX=(velocityX)-FloatConstants::Half;
    if ((velocityX)<FloatConstants::Two &&
        y>FloatConstants::Zero)
        velocityX=2.0f;
    if (y>FloatConstants::Zero && (animationStage)<14) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f;
            velocityY=0.0f;
            verticalAcceleration=0.0f;
            y=0.0f;
            ResetSecondaryCounter(0xE);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=12.5f;
        velocityY=8.5f;
        verticalAcceleration=0.65f;
    }
    if ((animationStage)==7 && (animationFrame)==0)
        Fighter::SpawnTrackedEffect(0x336,x,y,
            facing,1,0,1);
    if ((animationStage)==7 && (animationFrame)==0)
        PlaySharedSound(0x1D);
    if ((animationStage)==14 && (animationFrame)==0)
        ResetSecondaryCounter((animationStage)-2);
    break;
}
