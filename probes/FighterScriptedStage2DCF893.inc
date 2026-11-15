// F893 original game action2DC 660B/188-x86: true ground contact and stage phases.
// Native stage2 sprite33B, stage13 sprite338 and once-only auxiliary2.
// Stage15 12.5/15.0 motion, stage24 aux22, true random0..30 on getter match.
// Entire original 46,755B fighter still NONEXACT, not a callable inner case.
case 0x2DC: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
        velocityX=10.0f;
        velocityY=0.0f;
        SpawnDirectedAt453A70(0x33B,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnDirectedAt453A70(0x338,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(1);
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_F893FloatFallAt00657478;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<24) {
        velocityY=velocityY-g_F893VerticalStageAt006598B0;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(24);
            velocityX=0.0f;
            velocityY=0.0f;
            y=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(0,30);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(2);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=12.5f;
        velocityY=15.0f;
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==24 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(22);
    return;
}
