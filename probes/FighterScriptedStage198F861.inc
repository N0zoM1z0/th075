// F861 physically bounded native 198: 199B/60 x86/7 PE fields.
// True actor state2 and stage4, sprite351, signed facing*90 and Y global659460.
// Complete original game interior, giant original still nonexact.
case 0x198: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==4 && S16(0x64)==0) {
        PrepareActionAt453D40(3);
        SpawnFloatXYAt453A70(0x351,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*90)+F32(0x44),
            (*(&POS48))+g_F861ShotYAt00659460,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0xC8);
    }
    return;
}
