// F652 native complete D2 resource shot with real x87 speed scaling.
// Not a whole-function source match; this is an internal case.
case 0xD2: {
    if (I16(0x3B0)<2) {
        SetNativeActionAt40FAC0(9);
        break;
    }
    I16(0x3B0)=I16(0x3B0)-F652_DECAY;
    if (I16(0x62)==0 && I16(0x64)==0) {
#if F652_SCALE_BEFORE
        POS=POS*g_BounceScaleAt00657F74;
        F32(0x54)=F32(0x54)*g_BounceScaleAt00657F74;
        PrepareActionAt453D60(0x2C);
#endif
        SpawnWithFloatAt453A70(F652_SPRITE,I32(0x44),
                F32(0x48)+g_ContactProjectionAt00657888,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
#if !F652_SCALE_BEFORE
        POS=POS*g_BounceScaleAt00657F74;
        F32(0x54)=F32(0x54)*g_BounceScaleAt00657F74;
        PrepareActionAt453D60(0x2C);
#endif
    }
    // The original applies this x87 drag every frame, even outside
    // the stage/frame-zero projectile initialization path.
    POS54=POS54-F32(0x5C)*g_BounceScaleAt00657F74;
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        if (static_cast<unsigned int>(I32(0x4F4))>0)
            SetAuxActionAt40FB40(2);
        else
            SetNativeActionAt40FAC0(9);
    }
    break;
}
