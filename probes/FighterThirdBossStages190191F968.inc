// F968 original Japanese TH075 004AC040 actions 190 and 191.
 // Each complete original state: 597B/147 x86/11 native PE fields.
 // Normal source emits 561B/147x86, all ordered original mnemonics.
 // Each has TWELVE incorrect 6B-versus-3B x87 stack temp widths
 // (original EBP-0xA8..-0xD4, source much shallower) and 94
 // true GPR-role mismatches: original 82KB father NONEXACT.
 // Genuine three source projectile calls PER original state,
 // no compiled loop unrolling, original-byte grafts or filler locals.
// F968 natural original Japanese 004AC040 action 0x190, 597 B 147 native x86.
case 0x190: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>5 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4-8);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
           float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
           (*(&POS48))+g_F968_RoundY190At00659294,
           *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4-4);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
           float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
           (*(&POS48))+g_F968_RoundY190At00659294,
           *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4-12);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
           float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
           (*(&POS48))+g_F968_RoundY190At00659294,
           *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
// F968 natural original Japanese 004AC040 action 0x191, 597 B 147 native x86.
case 0x191: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4+30);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
           float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
           (*(&POS48))+g_F968_RoundY191At00659498,
           *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4+34);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
           float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
           (*(&POS48))+g_F968_RoundY191At00659498,
           *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4+26);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
           float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
           (*(&POS48))+g_F968_RoundY191At00659498,
           *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
