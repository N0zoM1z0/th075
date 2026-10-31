// F892 original 2DB whole 556B/162x86 native PE handler.
// Both actual borrowed float owner/this X left-lvalues preserve native x87 ordering.
// Native random range 455580 call and short+516 update are WITHIN current-action guard.
// Stage15 two real projectile methods; whole original 46755B fighter NONEXACT.
case 0x2DB: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=0;
        S16(0x80)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        ResetAt453E20();
    }
    if (S16(0x62)>1 && S16(0x62)<10) {
        if (F892AbsAt00412D90(
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44)
                <g_F892DistAt0065787C) {
            SetAuxActionAt40FB40(10);
            return;
        }
    }
    if (S16(0x62)>15) {
        POS=POS-g_BounceScaleAt00657F74;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(30,60);
    }
    if (S16(0x62)==2 && S16(0x64)==0)
        POS=12.5f;
    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(2);
    }
    if (S16(0x62)==15 && S16(0x64)==0) {
        SpawnFloatXRawYAt453C80(0x80,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*100)+F32(0x44),
            I32(0x48),(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnDirectedAt453A70(0x336,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(2);
    }
    if (S16(0x62)==16 && S16(0x64)==0)
        POS=17.5f;
    return;
}
