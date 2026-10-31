// F989 SHA-pinned Japanese original TH075 004AC040 action258:
 // physical 004B7BB0..004B7EF2, 834B/212 native x86, 15 real
 // original typed PE/COFF external fields. Five genuine separate
 // 0x325 shots with F02*3+100/95/90/85/80 and signed facing*97,
 // true Y global00659498, followed by animation0x64 and real
 // signed-short counters. Full-partial father source mnemonics and
 // instruction widths align, but 137 GPR roles still wrong.
 // Original 82KB whole game father remains NONEXACT.
// F989 original Japanese TH075 fighter 004AC040 action258
case 0x258: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF02)<3 && S16(0xF00)<=0) {
        PrepareActionAt453D40(0);
        F32(0x314)=float(S16(0xF02)*3+100);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+95);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+90);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+85);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+80);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x64);
        ++S16(0xF02);
        S16(0xF00)=3;
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
