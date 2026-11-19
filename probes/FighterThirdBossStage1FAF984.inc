// F984 true Japanese original 004AC040 action 1FA.
 // Physical original 004B6394..004B6824: 1168B/339 x86,
 // 28 genuine external PE fields and all mnemonic/width ordinals
 // aligned. Only six native GPR roles still wrong (local 327-333),
 // original receiver remains nonnative EBP, full giant NONEXACT.
case 0x1FA: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>30)
            color[0]=(color[0])-30;
        else {
            color[0]=0;
            ResetSecondaryCounter(8);
            velocityX=120.0f;
            velocityY=10.0f;
            field05C=0.4f;
            break;
        }
    }
    if ((animationStage)==9 || (animationStage)==10) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ClearMotionFields();
            ResetSecondaryCounter(0xB);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        Fighter::SpawnTrackedEffect(0x33E,
            float(RecordedRange(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RecordedRange(0,90)),
            1,1,0,1);
    if ((animationStage)==9 && (animationFrame)==0 && (scriptCounterF00)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++scriptCounterF00;
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(2);
        Fighter::SpawnTrackedEffect(0x338,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x339,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33A,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33B,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33C,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33D,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        ResetTransform(0.0f,0.0f,0.0f);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF02)<4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF02;
        break;
    }
    if ((animationStage)==11 && (animationFrame)==0)
        ResetSecondaryCounter(9);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
