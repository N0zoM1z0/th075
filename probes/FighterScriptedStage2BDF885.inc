// F885 original native 2BD 855B/239x86, original PE call topology.
// Sprite346 THEN PrepareD, new action2C2/Reset/ownerX-copy and early return.
// Stage5 sprite74, stage7 PrepareB, stage8 height30 and FILD-C8.
// Entire 46,755B fighter still NONEXACT, not independent callable code.
// F884 original game 2BC full 803B/228-x86, 22 original physical PE fields.
// Actual double gravity + phases7/9, stage5 FILD+FSUBR and stage8 floatX.
// Two actual native game motion(float,float,int) and full 901B afterRET tables.
// Enclosing 46755B original fighter still NONEXACT, no split case CODE credit.
case 0x2BD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        field080=1;
        ResetAt453E20();
    }
    if ((animationStage)>8) {
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
    }
    if ((reinterpret_cast<signed short&>(scriptCounterF00))==0 && field07C!=0) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        if (field07C==1) {
            SpawnExtraAt453B50(0x346,reinterpret_cast<int&>(x),
                (*(&y))+g_ContactProjectionAt00657888,
                (facing),1,0,1);
            PrepareActionAt453D40(0xD);
            SetNativeActionAt40FAC0(0x2C2);
            ResetAt453E20();
            reinterpret_cast<int&>(x)=reinterpret_cast<int&>(opponent->x);
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        AnimatePushAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x74,
            x-
                 float((facing)*64),
            (*(&y))+g_F884Stage5YAt00659470,
            (facing),1);
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        PrepareActionAt453D40(0xB);
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
        SetFloatMotionAt40FBB0(100.0f,60.0f,0);
        scaleX=3.0f;
        scaleY=0.05f;
        velocityX=30.0f;
        UpdateGaugeTimer(0x1F4);
        SpawnFloatXRawYAt453C80(0x80,
            float((facing)*150)+(x),
            reinterpret_cast<int&>(y),(facing),1);
    }
    return;
}
