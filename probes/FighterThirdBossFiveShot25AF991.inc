// F991 actual original Japanese TH075 004AC040 action25A.
 // Original game PE 004B823F..004B84BA 635B/166 x86/15
 // typed external call/global fields. FIVE non-looping
 // sprite0x325 shots at angles 10/5/0/5/10, each native
 // facing*97 float X and original global00659498 Y.
 // Source all mnemonics/widths match in whole partial
 // parent; 97 real GPR roles remain wrong, giant NONEXACT.
// F991 pinned original Japanese 004AC040 action 25A native five-shot
case 0x25A: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        F32(0x314)=10.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=5.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=0.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=5.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=10.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0xFA);
    }
    break;
}
