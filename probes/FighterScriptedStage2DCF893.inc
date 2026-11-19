// F893 original game action2DC 660B/188-x86: true ground contact and stage phases.
// Native stage2 sprite33B, stage13 sprite338 and once-only auxiliary2.
// Stage15 12.5/15.0 motion, stage24 aux22, true random0..30 on getter match.
// Entire original 46,755B fighter still NONEXACT, not a callable inner case.
case 0x2DC: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        field07C=0;
        field080=1;
        velocityX=10.0f;
        velocityY=0.0f;
        SpawnDirectedAt453A70(0x33B,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PlaySound(1);
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        SpawnDirectedAt453A70(0x338,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PlaySound(1);
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_F893FloatFallAt00657478;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<24) {
        velocityY=velocityY-g_F893VerticalStageAt006598B0;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetSecondaryCounter(24);
            velocityX=0.0f;
            velocityY=0.0f;
            y=0.0f;
            return;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RandomBoundaryAt455580(0,30);
    }
    if ((animationStage)==13 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(2);
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        velocityX=12.5f;
        velocityY=15.0f;
        field07C=0;
        field080=1;
    }
    if ((animationStage)==24 && (animationFrame)==0)
        ResetSecondaryCounter(22);
    return;
}
