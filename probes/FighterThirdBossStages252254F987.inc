// F987 original Japanese 004AC040 252/253/254, real native
 // physical 260B/72x86, 259B/72x86, 225B/63x86 respectively.
 // Source uses actual byte-prefix-decrement original MOV/SUB/MOV
 // (rather than incorrect MOVZX), gauge short side effects 252/253
 // and authentic stage6 shot 0x37 with opponent +0xEFA reset.
 // 254 has NO real afterRET DIR32 entry: source boundary via full
 // previous 253 instructions and real following 255 jump-table entry.
 // Native original 252/253 still have one AL/CL register-specific
 // x86 width mismatch each; 254 has zero mnemonic/width errors.
 // No internal exact credit, giant 82KB remains NONEXACT.
// F987 pinned native Japanese fighter 004AC040 real action 0x252.
case 0x252: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        --U8(0x366);
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
    }
    if (S16(0x3B6)==0 && I32(0x7C)==1)
        S16(0x3B0)=1000;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(0x21);
        *reinterpret_cast<signed short*>(OWNER+0xEFA)=0;
    }
    break;
}
// F987 pinned native Japanese fighter 004AC040 real action 0x253.
case 0x253: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        --U8(0x366);
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
    }
    if (S16(0x3B6)==0 && I32(0x7C)==1)
        S16(0x3B0)=1000;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(0x21);
        *reinterpret_cast<signed short*>(OWNER+0xEFA)=0;
    }
    break;
}
// F987 pinned native Japanese fighter 004AC040 real action 0x254.
case 0x254: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        --U8(0x366);
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(0x21);
        *reinterpret_cast<signed short*>(OWNER+0xEFA)=0;
    }
    break;
}
