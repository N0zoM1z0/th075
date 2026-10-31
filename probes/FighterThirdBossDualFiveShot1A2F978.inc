// F978 pinned Japanese original game fighter 004AC040 action1A2.
// 004B450B..004B4981 original 1142 CODE B /309 x86;
// BOTH actual +0x39D branches independently issue FIVE genuine
// 0x344 projectile calls with native angles 65,55,45,35,25.
// Ordinary parent C++ emits all 309 native mnemonics and widths,
// all 24 PE external fields; 171 true GPR-role errors persist.
// Entire original 82KB fighter still NONEXACT. No byte grafting.
// F978 physical original 004AC040 game action1A2: two 5-shot branches.
case 0x1A2: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        if (*reinterpret_cast<signed char*>(RAW+0x39D)==2) {
            F32(0x314)=65.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=55.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=45.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=35.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=25.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        } else {
            F32(0x314)=65.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=55.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=45.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=35.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            F32(0x314)=25.0f;
            F32(0x318)=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*47)+F32(0x44),
                (*(&POS48))+g_F969_RoundY192At00658264,
                *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        }
    }
    break;
}
