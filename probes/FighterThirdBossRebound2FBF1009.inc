// F1009 native original Japanese fighter 004AC040 2FB.
 // Original 004BF40E..004BF9A2 1428B/411x86/33 real physical
 // PE call and global fields. Real random0x33E, 6 native seven
 // arg 0x338..0x33D with FILD/FSUBR signed facing*7,
 // opponent facing via verified F752 borrowed native X,
 // world-X bounds 0065787C/0065920C, real stage8
 // randomized rebound and genuine transition to 0x2F9.
 // Source in normal PARTIAL father produces 1425B/411 x86
 // with ALL native mnemonic/GPR roles, one wrong final
 // shared-parent JMP width original 5B vs source2B.
 // Real 2FB restores preceding 2FA's last JMP to native5B;
 // original whole 82KB parent remains NONEXACT.
// F1009 original Japanese TH075 004AC040 2FB
case 0x2FB: {
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
            ResetSecondaryCounter(13);
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
        ResetPrimaryCounters(0x2F9);
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
        velocityX=float(RecordedRange(0,480)-240);
        if ((x)<g_F1009_LeftAt0065787C)
            velocityX=float((RecordedRange(0,180)+90) *
                (facing));
        if ((x)>g_F1009_RightAt0065920C)
            velocityX=float(-(RecordedRange(0,180)+90) *
                (facing));
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        if (x >
            opponent->x)
            facing=-1;
        else
            facing=1;
    }
    if ((animationStage)==13 && (animationFrame)==0)
        ResetSecondaryCounter(11);
    break;
}
