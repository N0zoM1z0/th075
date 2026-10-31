// F896 original 0x2E6: 374B/102 native x86, true random-action cascade.
// Start action 0x2E5 iff random F00<30 and occupied; stage3 sprite38E.
// No fake source locals; entire original 46755B father NONEXACT.
case 0x2E6: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=0;
        S16(0x80)=1;
    }
    POS=POS-g_F893FloatFallAt00657478;
    if (POS<g_ThresholdAt0065782C)
        POS=0.0f;
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        S16(0xF00)=RandomBoundaryAt455580(0,100);
        if (I32(0x7C)==0) {
            SetNativeActionAt40FAC0(0);
            S16(0x516)=RandomBoundaryAt455580(60,120);
            return;
        }
        if (S16(0xF00)<30) {
            SetNativeActionAt40FAC0(0x2E5);
            return;
        }
        if (S16(0xF00)<60) {
            SetNativeActionAt40FAC0(0x2E7);
            return;
        }
        SetNativeActionAt40FAC0(0x2E8);
        return;
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=15.0f;
        PrepareActionAt453D40(7);
        SpawnWithFloatAt453A70(0x38E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    return;
}
