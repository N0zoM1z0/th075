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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        field07C=1;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 || (reinterpret_cast<signed short&>(animationStage))==7) {
        if ((color[0])>20)
            color[0]=(color[0])-20;
        else
            color[0]=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>8 && (reinterpret_cast<signed short&>(animationStage))<13) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(13);
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
        SetNativeActionAt40FAC0(0x2F9);
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
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
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        SetAuxActionAt40FB40(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=float(RandAt455580(0,480)-240);
        if ((x)<g_F1009_LeftAt0065787C)
            velocityX=float((RandAt455580(0,180)+90) *
                (facing));
        if ((x)>g_F1009_RightAt0065920C)
            velocityX=float(-(RandAt455580(0,180)+90) *
                (facing));
        velocityY=3.0f;
        field05C=0.5f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==9 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
            reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
            facing=-1;
        else
            facing=1;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(11);
    break;
}
