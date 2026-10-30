// F833: physical original 005214B0 case C9, 279 native CODE B, 86 x86.
// Real x87 signed-direction projectile coordinates, borrowed true x
// member at this+0x44, and native epilogue direct return.
// This is an ORIGINAL INTERIOR only, NOT an independent exact function.
case 0xC9: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=-15.0f;
        SpawnAt453C80(0x7D,
            reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*80),
            (*(&POS48))+g_F701_VolleyYAt00658268,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    if (POS<g_ThresholdAt0065782C) {
        POS=POS+g_AnimationDeltaAt0065747C;
        if (POS>g_ThresholdAt0065782C) POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    return;
}
