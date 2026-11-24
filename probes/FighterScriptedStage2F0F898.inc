// F898 original native 2F0 complete 828B/229x86 with mixed float stage/DOUB gravity.
// Full original 46755B parent NONEXACT, not independently callable CODE.
case 0x2F0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        field07C=0;
        field080=1;
        ClearMotionFields();
    }
    if ((animationStage)<6) {
        ++scriptCounterF02;
        if ((scriptCounterF02)>4) {
            SpawnAuxEffect(0x3E,
                x-
                    float((facing)*40),
                (*(&y))+g_F898ShotYAt0065839C,1,1);
            scriptCounterF02=0;
        }
    }
    if ((animationStage)>10) {
        velocityX=(velocityX)-g_F884DoubleDropAt00657D00;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if ((animationStage)==7) {
        scaleX=(scaleX)+FloatConstants::OneFifth;
        scaleY=(scaleY)-g_F884PhaseYAt006598B8;
    }
    if ((animationStage)==9) {
        scaleX=(scaleX)-FloatConstants::OneFifth;
        scaleY=(scaleY)+g_F884PhaseYAt006598B8;
        velocityX=2.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        PlaySound(0xD);
        SpawnBattleEffect(0x38D,x,
            (*(&y))+GeometryConstants::Hundred,
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
    if ((animationStage)==10 && (animationFrame)==0) {
        scaleX=1.0f;
        scaleY=1.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        aiCardTimer=static_cast<short>(
            static_cast<int>(g_OptionsModeAt006714D0)*30+240);
        ResetTransform(100.0f,60.0f,0.0f);
        scaleX=3.0f;
        scaleY=0.05f;
        velocityX=20.0f;
        SpawnAuxEffect(0x80,
            float((facing)*150)+(x),
            y,(facing),1);
    }
    if ((animationStage)==11 && (animationFrame)==0)
        velocityX=15.0f;
    return;
}
