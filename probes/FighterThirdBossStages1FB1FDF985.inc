// F985 original Japanese game fighter 004AC040 1FB/1FC/1FD.
 // Physical native 1193/1192/1193 CODE B, 346 x86 each, 28
 // genuine typed original PE/COFF external fields EACH.
 // Stage6/7 opacity only (no false break), stage9..12 ground,
 // genuine six 0x338..0x33D signed-FSUBR bursts, real 0xC8
 // animation, stage8 counter/launch with X 60/-60/120 and stage13.
 // All 1038 original ordered mnemonics; one CMP opacity register
 // width wrong in 1FB and 1FC, zero wrong widths in 1FD.
 // Whole 82KB original remains NONEXACT, many GPR/EBP differences.
case 0x1FB: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=1;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>20)
            color[0]=(color[0])-20;
        else
            color[0]=0;

    }
    if ((animationStage)>8 && (animationStage)<13) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ClearMotionFields();
            ResetSecondaryCounter(0xD);
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
    if (AdvanceNestedFrame()==(animationStageCount))
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
        UpdateGaugeTimer(0xC8);
        ResetTransform(0.0f,0.0f,0.0f);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF02)<4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF02;
        break;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=60.0f;
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)==13 && (animationFrame)==0)
        ResetSecondaryCounter(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1FC: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=1;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>20)
            color[0]=(color[0])-20;
        else
            color[0]=0;

    }
    if ((animationStage)>8 && (animationStage)<13) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ClearMotionFields();
            ResetSecondaryCounter(0xD);
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
    if (AdvanceNestedFrame()==(animationStageCount))
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
        UpdateGaugeTimer(0xC8);
        ResetTransform(0.0f,0.0f,0.0f);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF02)<4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF02;
        break;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=-60.0f;
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)==13 && (animationFrame)==0)
        ResetSecondaryCounter(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1FD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=1;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>20)
            color[0]=(color[0])-20;
        else
            color[0]=0;

    }
    if ((animationStage)>8 && (animationStage)<13) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ClearMotionFields();
            ResetSecondaryCounter(0xD);
            y=0.0f;
            return;
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
    if (AdvanceNestedFrame()==(animationStageCount))
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
        UpdateGaugeTimer(0xC8);
        ResetTransform(0.0f,0.0f,0.0f);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF02)<4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF02;
        return;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=120.0f;
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)!=13)
        return;
    if ((animationFrame)!=0)
        return;
    ResetSecondaryCounter(0xB);
    return;
}
// F983 natural source probe for real original 004AC040 1F9
