// F887 original 2BF true native 473B/138-x86, two actual float->short FTOL calls.
// Stage0 short+80 0x63 THEN 1; stage2 sprites74/33D, stage10 Prepare7 and stage11 10f.
// Entire original fighter stays nonexact; no internal callable code credit.
// F886 actual original native 2BE 461B/136 x86/15 physical PE fields.
// Two true F32-to-short casts generate native __ftol2 original PE call 6406AC.
// Sprite33C needs actual RAW integer Y: floating formal adds nonnative FILD/FSTP.
// Whole original game fighter NONEXACT; no split-case acceptance.
case 0x2BF: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=0;
        S16(0x80)=0x63;
        S16(0x80)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x64)==0)
        I32(0x7C)=0;
    if (S16(0x62)==2 && S16(0x64)==0) {
        AnimatePushAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x74,
            reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-
                float((*reinterpret_cast<signed char*>(RAW+0x66))*64),
            (*(&POS48))+g_F884Stage5YAt00659470,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        S16(0xF00)=static_cast<signed short>(F32(0x44));
        S16(0xF02)=static_cast<signed short>(F32(0x48));
        SpawnExtraRawYAt453B50(0x33D,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1,0,1);
    }
    if (S16(0x62)==10 && S16(0x64)==0) {
        StartAnimationAt46D000(0x1F4);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==11 && S16(0x64)==0) {
        InitTrajectoryAt453E60(10.0f);
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    return;
}
