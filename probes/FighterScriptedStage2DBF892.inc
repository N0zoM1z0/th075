// F892 original 2DB whole 556B/162x86 native PE handler.
// Both actual borrowed float owner/this X left-lvalues preserve native x87 ordering.
// Native random range 455580 call and short+516 update are WITHIN current-action guard.
// Stage15 two real projectile methods; whole original 46755B fighter NONEXACT.
case 0x2DB: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=0;
        field080=1;
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        ClearMotionFields();
    }
    if ((animationStage)>1 && (animationStage)<10) {
        if (AbsFloatAt00412D90(
                opponent->x-x)
                <g_F892DistAt0065787C) {
            ResetSecondaryCounter(10);
            return;
        }
    }
    if ((animationStage)>15) {
        velocityX=(velocityX)-g_BounceScaleAt00657F74;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RecordedRange(30,60);
    }
    if ((animationStage)==2 && (animationFrame)==0)
        velocityX=12.5f;
    if ((animationStage)==10 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(2);
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        SpawnAuxEffect(0x80,
            float((facing)*100)+(x),
            y,(facing),1);
        SpawnBattleEffect(0x336,x,y,
            (facing),1);
        PlaySound(2);
    }
    if ((animationStage)==16 && (animationFrame)==0)
        velocityX=17.5f;
    return;
}
