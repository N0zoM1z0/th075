// F839 real original selected 005214B0 caseCC 428B/126-x86/10 real PE fields.
// Native float evaluation order y+velocityY and vtable call OUTSIDE
// conditional stage-short decrement. Genuine direct parent exits.
// Not an independently callable original game function.
case 0xCC: {
    if (y==g_ThresholdAt0065782C || velocityY>g_ThresholdAt0065782C) {
        SetupCollisionAt454BC0(3,4,0xFF);
        field088=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ClearMotionFields();
    if (animationStage>2) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            return;
        }
    }
    if (animationStage==4 && velocityY<g_ExtraThresholdAt00657D14)
        ResetSecondaryCounter(5);
    ++animationFrame;
    if (animationFrame>=field072) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==3) {
            velocityX=0.0f;
            velocityY=23.0f;
            field05C=0.75f;
            SpawnAuxEffect(0x3C,x,y,1,1);
            field3AC=0;
        }
        if (animationStage>=field070)
            animationStage=animationStage-2;
        BindAnimation();
    }
    return;
}
