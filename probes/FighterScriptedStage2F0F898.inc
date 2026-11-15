// F898 original native 2F0 complete 828B/229x86 with mixed float stage/DOUB gravity.
// Full original 46755B parent NONEXACT, not independently callable CODE.
case 0x2F0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        field07C=0;
        field080=1;
        ResetAt453E20();
    }
    if ((animationStage)<6) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>4) {
            SpawnAt453C80(0x3E,
                reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-
                    float((facing)*40),
                (*(&y))+g_F898ShotYAt0065839C,1,1);
            reinterpret_cast<signed short&>(scriptCounterF02)=0;
        }
    }
    if ((animationStage)>10) {
        velocityX=(velocityX)-g_F884DoubleDropAt00657D00;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if ((animationStage)==7) {
        scaleX=(scaleX)+g_F865SustainScaleAt00658348;
        scaleY=(scaleY)-g_F884PhaseYAt006598B8;
    }
    if ((animationStage)==9) {
        scaleX=(scaleX)-g_F865SustainScaleAt00658348;
        scaleY=(scaleY)+g_F884PhaseYAt006598B8;
        velocityX=2.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        PrepareActionAt453D40(0xD);
        SpawnWithFloatAt453A70(0x38D,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==7 && (animationFrame)==0) {
        PrepareActionAt453D40(0xA);
        SetFloatMotionAt40FBB0(-200.0f,60.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        reinterpret_cast<signed char&>(color[0])=-1;
        reinterpret_cast<signed char&>(color[1])=-1;
        reinterpret_cast<signed char&>(color[2])=-1;
        reinterpret_cast<signed char&>(color[3])=-1;
    }
    if ((animationStage)==10 && (animationFrame)==0) {
        scaleX=1.0f;
        scaleY=1.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        aiCardTimer=static_cast<short>(
            static_cast<int>(g_CloudOpponentAt006714D0)*30+240);
        SetFloatMotionAt40FBB0(100.0f,60.0f,0);
        scaleX=3.0f;
        scaleY=0.05f;
        velocityX=20.0f;
        SpawnFloatXRawYAt453C80(0x80,
            float((facing)*150)+(x),
            reinterpret_cast<int&>(y),(facing),1);
    }
    if ((animationStage)==11 && (animationFrame)==0)
        velocityX=15.0f;
    return;
}
