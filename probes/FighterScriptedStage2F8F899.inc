// F899 actual native 2F8 complex 1151B/316x86 real source and PE calls.
// Stage8 true integer random->float height and stage12/13 CloudOpponent test.
// Native owner sprites393,392,80; do not credit inner case as whole CODE.
case 0x2F8: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
        field07C=0;
        field080=1;
        ClearMotionFields();
    }
    if ((animationStage)<6 && (animationFrame)<10) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>4) {
            SpawnAt453C80(0x3E,
                x-
                    float((facing)*40),
                (*(&y))+g_F898ShotYAt0065839C,1,1);
            reinterpret_cast<signed short&>(scriptCounterF02)=0;
        }
    }
    if ((animationStage)>13) {
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
        PlaySound(0xD);
        SpawnBattleEffect(0x393,x,0.0f,
            (facing),1);
    }
    if ((animationStage)>6 && (animationStage)<13) {
        SpawnBattleEffect(0x392,
            (x)+g_ContactProjectionAt00657888-
                float(RecordedRange(0,200)),
            (*(&y))+g_F701_VolleyYAt00658268,
            (facing),1);
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==7 && (animationFrame)==0) {
        PlaySound(0xA);
        ResetTransform(-200.0f,60.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        reinterpret_cast<signed char&>(color[0])=-1;
        reinterpret_cast<signed char&>(color[1])=-1;
        reinterpret_cast<signed char&>(color[2])=-1;
        reinterpret_cast<signed char&>(color[3])=-1;
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        scaleX=1.0f;
        scaleY=1.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        ResetTransform(100.0f,60.0f,0.0f);
        scaleX=3.0f;
        scaleY=0.05f;
        velocityX=float(RecordedRange(0,60))+
            g_ApproachUpperAt006592A4;
        SpawnFloatXRawYAt453C80(0x80,
            float((facing)*150)+(x),
            reinterpret_cast<int&>(y),(facing),1);
    }
    if ((animationStage)==13-static_cast<int>(g_CloudOpponentAt006714D0)
        && (animationFrame)==0
        && (fieldF04)<static_cast<int>(g_CloudOpponentAt006714D0)+1) {
        ++fieldF04;
        ResetSecondaryCounter(7);
        PlaySound(0xA);
        ResetTransform(-200.0f,60.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        reinterpret_cast<signed char&>(color[0])=-1;
        reinterpret_cast<signed char&>(color[1])=-1;
        reinterpret_cast<signed char&>(color[2])=-1;
        reinterpret_cast<signed char&>(color[3])=-1;
        facing=
            -(facing);
    }
    if ((animationStage)==14 && (animationFrame)==0)
        velocityX=15.0f;
    return;
}
