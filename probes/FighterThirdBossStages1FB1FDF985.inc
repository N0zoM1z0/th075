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
        ResetAt453E20();
        field07C=1;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
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
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        SetAuxActionAt40FB40(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=60.0f;
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)==13 && (animationFrame)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1FC: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetAt453E20();
        field07C=1;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
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
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        SetAuxActionAt40FB40(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=-60.0f;
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)==13 && (animationFrame)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1FD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetAt453E20();
        field07C=1;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
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
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        SetAuxActionAt40FB40(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        velocityX=120.0f;
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((animationStage)==13 && (animationFrame)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
