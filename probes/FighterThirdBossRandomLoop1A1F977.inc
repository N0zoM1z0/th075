// F977 native Japanese TH075 original fighter action1A1, physical
// 004B42D1..004B450B, 570B/151 x86/12 true original PE fields.
// Real 5/8 shot loops with 30/20 - shot*10 + Rand(0,80/100)
// face-adjusted X require a live saved ESI across random calls.
// Natural whole VC7.1 source now emits original ESI PUSH prologue,
// complete 151 native mnemonic+width roles, but 67 GPR mismatches.
// Actual full original 82KB fighter remains NONEXACT, not case exact.
case 0x1A1: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        if (*reinterpret_cast<signed char*>(RAW+0x39D)==2) {
            for (int shot=0;shot<5;++shot) {
                F32(0x314)=30.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((30-shot*10+RandAt455580(0,80))*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F976_RandomYAt0065786C+shot*40)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        } else {
            for (int shot=0;shot<8;++shot) {
                F32(0x314)=30.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((20-shot*10+RandAt455580(0,100))*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F976_RandomYAt0065786C+shot*30)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        }
    }
    break;
}
