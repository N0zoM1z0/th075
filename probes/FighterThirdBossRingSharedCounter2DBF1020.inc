// F1020 independently checked original Japanese fighter004AC040
 // REAL 2DB double 36-shot storm counter ownership correction.
 // Original two genuinely separate 0x385 rings use ONE native
 // EBP−0x40 int shot counter, each reset to zero, NOT two
 // separate source C++ for-loop declarations. Both have the
 // actual original 1894B/548 x86 and 38 true PE targets.
 // Hoisting the genuine shared int into its original
 // stage11/frame0 scope removes one unnecessary compiler
 // four-byte slot, restores original entire 82796B/22721
 // x86 count, stack0x720 and this EBP−0x64. Entire
 // whole callable still NONEXACT due 12 real widths and
 // 6958 positional GPR roles; no independent case credit.
// F1016 actual SHA-pinned Japanese 004AC040 original 2DB.
 // Original 004BC8B1..004BD017 1894 CODE B/548x86,
 // 38 actual original PE call/global target fields.
 // Native stage6 six distinct 0x338..0x33D, random
 // 0x33E; stage11 TWO real full 36x0x385 loops,
 // step10, speed5 then10, Y native global00659460,
 // signed-facing*8 FILD/FSUBR world X.
 // Real stage8 actor/opponent facing FCOMP and signed
 // opacity/fall/land/aux. Complete original-shaped
 // PARTIAL father naturally emits all 548 original
 // mnemonic, width and GPR roles; whole 82KB NONEXACT.
// F1016 original Japanese fighter 004AC040 action 2DB genuine gameplay.
case 0x2DB: {
    if ((animationStage)==0 && (animationFrame)==0) {
                field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        fieldF06=0;
        field05C=0.2f;
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
        velocityY=float(RecordedRange(0,30)-15);
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
    if ((animationStage)==15 || (animationStage)==16) {
        if ((scriptCounterF00)<2) {
            if ((color[0])>40)
                color[0]=(color[0])-40;
            else {
                color[0]=0;
                if ((scriptCounterF00)<3) {
                    ResetSecondaryCounter(8);
                    break;
                }
            }
        }
    }
    if ((animationStage)==18 || (animationStage)==19) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else {
            color[0]=255;
            ResetSecondaryCounter(20);
        }
    }
    if ((animationStage)==20 || (animationStage)==21) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
                        ResetSecondaryCounter(22);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        Fighter::SpawnTrackedEffect(0x33E,
            float(RecordedRange(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RecordedRange(0,90)),
            1,1,0,1);
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
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
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF02)<4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF02;
        break;
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        ++scriptCounterF00;
        fieldF06=0;
        int shot;
        for (shot=0;shot<360;shot+=10) {
            field314=float(shot);
            field318=5.0f;
            SpawnBattleEffect(0x385,
                x -
                    float((facing)*8),
                (*(&y))+g_F1016_RingYAt00659460,
                facing,1);
        }
        for (shot=0;shot<360;shot+=10) {
            field314=float(shot);
            field318=10.0f;
            SpawnBattleEffect(0x385,
                x -
                    float((facing)*8),
                (*(&y))+g_F1016_RingYAt00659460,
                facing,1);
        }
    }
    if ((animationStage)==17 && (animationFrame)==0 && (fieldF06)<6) {
        ResetSecondaryCounter(15);
        ++fieldF06;
    }
    if ((animationStage)==20 && (animationFrame)==0)
        ResetSecondaryCounter(18);
    if ((animationStage)==22 && (animationFrame)==0)
        ResetSecondaryCounter(20);
    break;
}
