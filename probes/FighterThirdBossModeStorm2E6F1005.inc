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
        ResetAt453E20();
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
        reinterpret_cast<signed short&>(fieldF06)=30;
        reinterpret_cast<signed short&>(fieldF08)=1;
        field05C=0.15f;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>30)
            color[0]=(color[0])-30;
        else {
            color[0]=0;
            SetAuxActionAt40FB40(8);
            break;
        }
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=float(RandAt455580(0,100)-50);
        velocityY=float(RandAt455580(0,5)+20);
        if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
                reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
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
                ResetAt453E20();
                SetAuxActionAt40FB40(19);
                y=0.0f;
                break;
            }
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((animationStage)>10 && (animationStage)<17 && (reinterpret_cast<signed short&>(scriptCounterF02))==0) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if (g_F1004_ModeAt006714D0==0) {
            for (int shot=0;shot<12;++shot) {
                field314=float(shot*30);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_F1004_ModeAt006714D0==1) {
            for (int shot=0;shot<20;++shot) {
                field314=float(shot*18);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_F1004_ModeAt006714D0==2) {
            for (int shot=0;shot<30;++shot) {
                field314=float(shot*12);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_F1004_ModeAt006714D0==3) {
            for (int shot=0;shot<40;++shot) {
                field314=float(shot*9);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
    }
    if (GetNativeActionAt40FA30()==(field070)) {
        SetNativeActionAt40FAC0(0);
        aiCardTimer=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<4) {
        SetAuxActionAt40FB40(6);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        break;
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
    }
    if ((animationStage)==11 && (animationFrame)==0)
        PrepareActionAt453D40(5);
    if ((animationStage)==17 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
        SetAuxActionAt40FB40(15);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if ((animationStage)==19 && (animationFrame)==0)
        SetAuxActionAt40FB40(17);
    break;
}
