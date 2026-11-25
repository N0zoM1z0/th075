// F847 selected Japanese original 0x135: 278B/82-x86, 7 native PE fields.
// Actual signed facing byte, original kind/stage and natural C++ source.
// Interior only, not independent original exact callable CODE.
case 0x135: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
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
    if ((animationStage)==7 && (animationFrame)==0)
        SpawnBattleEffect(0x339,x,y,
            (facing),1);
    if ((animationStage)==7 && (animationFrame)==0)
        PlaySharedSound(0x1D);
    return;
}
