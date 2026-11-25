// F873 original game 1FB: full 253B/70x86 native case, physics before stage0.
// Real height global658350, stage6 owner counters & POS15, independent game entry.
// Enclosing whole giant remains nonexact; no split-case exact CODE.
case 0x1FB: {
    if ((velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::ThreeQuarters;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
        field3AC=0;
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0)
        velocityX=15.0f;
    return;
}
