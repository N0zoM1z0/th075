// F860 native original game 196: 199B/60 x86/7 real PE call/global fields.
// Actual stage3 prepare3 -> sprite353 float XY -> animationC8.
// Natural float Y lvalue preserves native FLD member then FADD global.
// Whole original fighter nonexact; no split-case exact CODE.
case 0x196: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        PrepareActionAt453D40(3);
        SpawnFloatXYAt453A70(0x353,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*100)+F32(0x44),
            (*(&POS48))+g_F860ShotYAt006581DC,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0xC8);
    }
    return;
}
