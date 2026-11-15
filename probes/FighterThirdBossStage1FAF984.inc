// F984 true Japanese original 004AC040 action 1FA.
 // Physical original 004B6394..004B6824: 1168B/339 x86,
 // 28 genuine external PE fields and all mnemonic/width ordinals
 // aligned. Only six native GPR roles still wrong (local 327-333),
 // original receiver remains nonnative EBP, full giant NONEXACT.
case 0x1FA: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 || (reinterpret_cast<signed short&>(animationStage))==7) {
        if ((color[0])>30)
            color[0]=(color[0])-30;
        else {
            color[0]=0;
            SetAuxActionAt40FB40(8);
            velocityX=120.0f;
            velocityY=10.0f;
            field05C=0.4f;
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==9 || (reinterpret_cast<signed short&>(animationStage))==10) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xB);
            y=0.0f;
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))<8 && (reinterpret_cast<signed short&>(animationStage))>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((reinterpret_cast<signed short&>(animationStage))==9 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
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
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        SetAuxActionAt40FB40(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(9);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
