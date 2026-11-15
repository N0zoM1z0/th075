// F894 original 2DD physical native complete 535B/153x86, next physical handler 2E4.
// Stage3 truly used random0..6 FILD EBP-0x10C, stage18 sprite335 and stage26 aux24.
// This is an inner case, whole 46755B fighter NONEXACT and uncredited.
case 0x2DD: {
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
    }
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<26) {
        velocityY=velocityY-g_F894VerticalStageAt00659090;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(26);
            velocityX=0.0f;
            velocityY=0.0f;
            y=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(0,60);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        velocityX=float(RandomBoundaryAt455580(0,6))+g_F894RandomHeightAt006592A0;
        velocityY=16.0f;
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==18 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnDirectedAt453A70(0x335,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(4);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==26 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(24);
    return;
}
