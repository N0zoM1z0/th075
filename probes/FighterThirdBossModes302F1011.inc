// F1011 original Japanese 004AC040 fighter 302.
 // Native 004BF9A2..004BFDAB: 1033B/279 x86/25 PE.
 // Four authentic mode0/1/2/3 signed shot loops of
 // 10/12/15/20 sprite0x389, step36/30/24/18,
 // FILD facing*16 FSUBR world-X and Y+0065836C,
 // native motion threshold and ground return.
 // All 279 original mnemonic/GPR roles, only
 // last shared-tail JMP width native5 vs source2.
 // Adding genuine 302 corrects previous 2FB's
 // last near JMP and restores all 411 native widths.
 // Whole 82KB father remains NONEXACT.
// F1011 pinned Japanese original 004AC040 game action302.
case 0x302: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF08)=g_F1004_ModeAt006714D0+2;
    }
    if (S16(0x62)<13 && POS48>=g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS54<=g_AnimationDeltaAt0065747C)
            POS54=1.0f;
    }
    if (S16(0x62)>12 && POS48>=g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(15);
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(
            RandAt455580(0,60)+180-g_F1004_ModeAt006714D0*20);
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS54=13.5f;
        POS5C=0.5f;
    }
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(5);
        if (g_F1004_ModeAt006714D0==0) {
            for (int shot=0;shot<10;++shot) {
                F32(0x314)=float(shot*36);
                F32(0x318)=4.0f;
                SpawnFloatXYAt453A70(0x389,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
        if (g_F1004_ModeAt006714D0==1) {
            for (int shot=0;shot<12;++shot) {
                F32(0x314)=float(shot*30);
                F32(0x318)=4.0f;
                SpawnFloatXYAt453A70(0x389,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
        if (g_F1004_ModeAt006714D0==2) {
            for (int shot=0;shot<15;++shot) {
                F32(0x314)=float(shot*24);
                F32(0x318)=4.0f;
                SpawnFloatXYAt453A70(0x389,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
        if (g_F1004_ModeAt006714D0==3) {
            for (int shot=0;shot<20;++shot) {
                F32(0x314)=float(shot*18);
                F32(0x318)=4.0f;
                SpawnFloatXYAt453A70(0x389,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
    }
    break;
}
