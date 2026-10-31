// F883 native action259 PHYSICAL 206B/60x86/6 PE fields ends at action2BC.
// Numeric successor 25A is default, NOT native physical successor.
// Actual facing FILD EBP-B8 sprite34D and animation46D000(1F4).
// Complete giant remains nonexact; no internal action callable credit.
// F881 original native action258 206B/60 x86/6 genuine physical PE fields.
// Stage2 sprite340 float X from FILD signed facing*80, original raw integer Y.
// Native narrow char parameter, StartAnimation46D000(FA), Prepare5.
// Enclosing full fighter NONEXACT; no separate callable case credit.
case 0x259: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=1;
        FLAG=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        SpawnFloatXRawYAt453A70(0x34D,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            I32(0x48),(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0x1F4);
        PrepareActionAt453D40(5);
    }
    return;
}
