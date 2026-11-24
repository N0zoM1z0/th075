// F1005 original Japanese 004AC040 native state2E6:
 // 2058 original CODE B/590x86, 47 real native PE targets.
 // Four real signed-mode loops emit 12/20/30/40 shots at
 // angle step30/18/12/9, each 0x387 signed facing*16
 // FILD/FSUBR; true random 0x33E and six 0x338..0x33D
 // seven-argument calls. Reused original borrowed F752
 // X views preserve direct native FCOMP memory: all 590
 // mnemonic + GPR roles match; only final shared-tail JMP
 // 5B original vs 2B partial-parent width differs.
 // Whole 82KB fighter and saved-this EBP NONEXACT.
// F1005 pinned Japanese TH075 original 004AC040 2E6.
case 0x2E6: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        fieldF06=30;
        fieldF08=1;
        field05C=0.15f;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>30)
            color[0]=(color[0])-30;
        else {
            color[0]=0;
            ResetSecondaryCounter(8);
            break;
        }
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=float(RecordedRange(0,100)-50);
        velocityY=float(RecordedRange(0,5)+20);
        if (x >
                opponent->x)
            facing=-1;
        else
            facing=1;
    }
    if ((animationStage)==9) {
        if ((color[0])<225)
            color[0]=(color[0])+30;
        else
            color[0]=255;
    }
    if ((animationStage)>13 && (animationStage)<19) {
        if (y>g_ThresholdAt0065782C) {
            velocityY=velocityY-field05C;
            if (y+velocityY<=g_ThresholdAt0065782C) {
                color[0]=255;
                ClearMotionFields();
                ResetSecondaryCounter(19);
                y=0.0f;
                break;
            }
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        Fighter::SpawnTrackedEffect(0x33E,
            float(RecordedRange(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RecordedRange(0,90)),
            1,1,0,1);
    if ((animationStage)>10 && (animationStage)<17 && (scriptCounterF02)==0) {
        ++scriptCounterF02;
        if (g_OptionsModeAt006714D0==0) {
            for (int shot=0;shot<12;++shot) {
                field314=float(shot*30);
                SpawnBattleEffect(0x387,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_OptionsModeAt006714D0==1) {
            for (int shot=0;shot<20;++shot) {
                field314=float(shot*18);
                SpawnBattleEffect(0x387,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_OptionsModeAt006714D0==2) {
            for (int shot=0;shot<30;++shot) {
                field314=float(shot*12);
                SpawnBattleEffect(0x387,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_OptionsModeAt006714D0==3) {
            for (int shot=0;shot<40;++shot) {
                field314=float(shot*9);
                SpawnBattleEffect(0x387,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(
            RecordedRange(60,120)-g_OptionsModeAt006714D0*20);
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(2);
        Fighter::SpawnTrackedEffect(0x338,
            x -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x339,
            x -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33A,
            x -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33B,
            x -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33C,
            x -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        Fighter::SpawnTrackedEffect(0x33D,
            x -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        ResetTransform(0.0f,0.0f,0.0f);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF00;
        break;
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
    }
    if ((animationStage)==11 && (animationFrame)==0)
        PlaySound(5);
    if ((animationStage)==17 && (animationFrame)==0 && (scriptCounterF00)<10) {
        ResetSecondaryCounter(15);
        ++scriptCounterF00;
    }
    if ((animationStage)==19 && (animationFrame)==0)
        ResetSecondaryCounter(17);
    break;
}
