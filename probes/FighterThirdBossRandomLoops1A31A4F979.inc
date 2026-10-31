// F979 original Japanese 82KB fighter at 004AC040 real 1A3/1A4.
 // 1A3 physical 004B4981..004B4BAD, 556B/147x86, 11 genuine PE targets;
 // 1A4 physical 004B4BAD..004B4DE7, 570B/151x86, 11 true PE targets.
 // Unlike earlier 1A0/1A1, real 1A3/1A4 have no Reset at stage0,
 // both decrease vertical speed and complete animation with action 9.
 // 1A3 has signed X 30/20 + random; 1A4 uses shot*10+Rand+30/20.
 // Ordinary VC7.1 parent emits all native mnemonic/width roles but
 // 67/71 GPR roles wrong. Still NONEXACT entire 82KB original.
case 0x1A3: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
    }
    POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        if (*reinterpret_cast<signed char*>(RAW+0x39D)==2) {
            for (int shot=0;shot<5;++shot) {
                F32(0x314)=0.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((RandAt455580(0,80)+30)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F979_RandomYAt00657858+shot*30)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        } else {
            for (int shot=0;shot<8;++shot) {
                F32(0x314)=0.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((RandAt455580(0,100)+20)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F979_RandomYAt00657858+shot*20)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        }
    }
    break;
}
case 0x1A4: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
    }
    POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        if (*reinterpret_cast<signed char*>(RAW+0x39D)==2) {
            for (int shot=0;shot<5;++shot) {
                F32(0x314)=-30.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((shot*10+RandAt455580(0,80)+30)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F976_RandomYAt0065786C+shot*40)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        } else {
            for (int shot=0;shot<8;++shot) {
                F32(0x314)=-30.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((shot*10+RandAt455580(0,100)+20)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F976_RandomYAt0065786C+shot*30)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        }
    }
    break;
}
