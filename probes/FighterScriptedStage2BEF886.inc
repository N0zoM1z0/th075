// F886 actual original native 2BE 461B/136 x86/15 physical PE fields.
// Two true F32-to-short casts generate native __ftol2 original PE call 6406AC.
// Sprite33C needs actual RAW integer Y: floating formal adds nonnative FILD/FSTP.
// Whole original game fighter NONEXACT; no split-case acceptance.
case 0x2BE: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        field080=6;
        ClearMotionFields();
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationFrame)==0)
        field07C=0;
    if ((animationStage)==2 && (animationFrame)==0) {
        AnimatePushAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x73,
            x-
                float((facing)*64),
            (*(&y))+g_F884Stage5YAt00659470,
            (facing),1);
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<signed short>(x);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<signed short>(y);
        SpawnExtraRawYAt453B50(0x33C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1,0,1);
    }
    if ((animationStage)==10 && (animationFrame)==0) {
        UpdateGaugeTimer(0x1F4);
        PrepareActionAt453D40(6);
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        InitTrajectoryAt453E60(5.0f);
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    }
    return;
}
