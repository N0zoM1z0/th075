// F893 original game action2DC 660B/188-x86: true ground contact and stage phases.
// Native stage2 sprite33B, stage13 sprite338 and once-only auxiliary2.
// Stage15 12.5/15.0 motion, stage24 aux22, true random0..30 on getter match.
// Entire original 46,755B fighter still NONEXACT, not a callable inner case.
case 0x2DC: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        collisionResult=0;
        remainingHits=1;
        velocityX=10.0f;
        velocityY=0.0f;
        SpawnBattleEffect(0x33B,x,y,
            (facing),1);
        PlaySound(1);
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        SpawnBattleEffect(0x338,x,y,
            (facing),1);
        PlaySound(1);
    }
    if ((velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::Half;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (y>FloatConstants::Zero && (animationStage)<24) {
        velocityY=velocityY-FloatConstants::SixtyFiveHundredths;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetSecondaryCounter(24);
            velocityX=0.0f;
            velocityY=0.0f;
            y=0.0f;
            return;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RecordedRange(0,30);
    }
    if ((animationStage)==13 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(2);
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        velocityX=12.5f;
        velocityY=15.0f;
        collisionResult=0;
        remainingHits=1;
    }
    if ((animationStage)==24 && (animationFrame)==0)
        ResetSecondaryCounter(22);
    return;
}
