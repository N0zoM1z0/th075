// F651 actual native D1 resource-gated movement and projectile shot.
// Source fragment belongs inside still-NONEXACT giant fighter Advance().
case 0xD1: {
    if (I16(0x3B0)<2) {
        SetNativeActionAt40FAC0(0);
        break;
    }
    I16(0x3B0)=I16(0x3B0)-F651_DECAY;
    if (I16(0x62)==0 && I16(0x64)==0) {
        ResetAt453E20();
        PrepareActionAt453D60(0x2C);
        SpawnWithFloatAt453A70(F651_SPRITE,I32(0x44),
                F32(0x48)+g_ContactProjectionAt00657888,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        if (static_cast<unsigned int>(I32(0x4F4))>0)
            SetAuxActionAt40FB40(2);
        else
            SetNativeActionAt40FAC0(0);
    }
    break;
}
