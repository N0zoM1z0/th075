// F978 pinned Japanese original game fighter 004AC040 action1A2.
// 004B450B..004B4981 original 1142 CODE B /309 x86;
// BOTH actual +0x39D branches independently issue FIVE genuine
// 0x344 projectile calls with native angles 65,55,45,35,25.
// Ordinary parent C++ emits all 309 native mnemonics and widths,
// all 24 PE external fields; 171 true GPR-role errors persist.
// Entire original 82KB fighter still NONEXACT. No byte grafting.
// F978 physical original 004AC040 game action1A2: two 5-shot branches.
case 0x1A2: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(2);
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(0);
        if (field39D==2) {
            field314=65.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=55.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=45.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=35.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=25.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
        } else {
            field314=65.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=55.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=45.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=35.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
            field314=25.0f;
            field318=10.0f;
            SpawnSevenFloatAt453B50(0x344,
                float((facing)*47)+(x),
                (*(&y))+g_F969_RoundY192At00658264,
                facing,1,0,1);
        }
    }
    break;
}
