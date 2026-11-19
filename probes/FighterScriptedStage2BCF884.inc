// F884 original game 2BC full 803B/228-x86, 22 original physical PE fields.
// Actual double gravity + phases7/9, stage5 FILD+FSUBR and stage8 floatX.
// Two actual native game motion(float,float,int) and full 901B afterRET tables.
// Enclosing 46755B original fighter still NONEXACT, no split case CODE credit.
case 0x2BC: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=0;
        field080=1;
        ClearMotionFields();
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
    if ((scriptCounterF00)==0 && field07C!=0) {
        ++scriptCounterF00;
        if (field07C==1) {
            PlaySound(0xD);
            Fighter::SpawnTrackedEffect(0x346,x,
                (*(&y))+g_ContactProjectionAt00657888,
                (facing),1,0,1);
        }
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        PlaySharedSound(0x17);
        SpawnAuxEffect(0x73,
            x-
                 float((facing)*64),
            (*(&y))+g_F884Stage5YAt00659470,
            (facing),1);
    }
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
        ResetTransform(100.0f,60.0f,0.0f);
        scaleX=3.0f;
        scaleY=0.05f;
        velocityX=20.0f;
        UpdateGaugeTimer(0x1F4);
        SpawnAuxEffect(0x80,
            float((facing)*150)+(x),
            y,(facing),1);
    }
    return;
}
