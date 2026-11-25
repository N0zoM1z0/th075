// F899 actual native 2F8 complex 1151B/316x86 real source and PE calls.
// Stage8 true integer random->float height and stage12/13 CloudOpponent test.
// Native owner sprites393,392,80; do not credit inner case as whole CODE.
case 0x2F8: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        collisionResult=0;
        remainingHits=1;
        ClearMotionFields();
    }
    if ((animationStage)<6 && (animationFrame)<10) {
        ++scriptCounterF02;
        if ((scriptCounterF02)>4) {
            SpawnAuxEffect(0x3E,
                x-
                    float((facing)*40),
                (*(&y))+GeometryConstants::ThirtyFive,1,1);
            scriptCounterF02=0;
        }
    }
    if ((animationStage)>13) {
        velocityX=(velocityX)-FloatConstants::OneDouble;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if ((animationStage)==7) {
        scaleX=(scaleX)+FloatConstants::OneFifth;
        scaleY=(scaleY)-FloatConstants::NineteenHundredths;
    }
    if ((animationStage)==9) {
        scaleX=(scaleX)-FloatConstants::OneFifth;
        scaleY=(scaleY)+FloatConstants::NineteenHundredths;
        velocityX=2.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        PlaySound(0xD);
        SpawnBattleEffect(0x393,x,0.0f,
            (facing),1);
    }
    if ((animationStage)>6 && (animationStage)<13) {
        SpawnBattleEffect(0x392,
            (x)+GeometryConstants::Hundred-
                float(RecordedRange(0,200)),
            (*(&y))+GeometryConstants::Eighty,
            (facing),1);
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==7 && (animationFrame)==0) {
        PlaySound(0xA);
        ResetTransform(-200.0f,60.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
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
            GeometryConstants::TwentyFive;
        SpawnAuxEffect(0x80,
            float((facing)*150)+(x),
            y,(facing),1);
    }
    if ((animationStage)==13-static_cast<int>(g_OptionsModeAt006714D0)
        && (animationFrame)==0
        && (fieldF04)<static_cast<int>(g_OptionsModeAt006714D0)+1) {
        ++fieldF04;
        ResetSecondaryCounter(7);
        PlaySound(0xA);
        ResetTransform(-200.0f,60.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        facing=
            -(facing);
    }
    if ((animationStage)==14 && (animationFrame)==0)
        velocityX=15.0f;
    return;
}
