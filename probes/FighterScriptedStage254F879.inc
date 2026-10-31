// F879 actual real game 0x254, whole original PE switch entry.
// Native true BYTE decrement (not MOVZX dword), stage5 floatY sprite37, owner+EFA reset.
// 252/253 include native +3B6/+7C guard; 254 does not. Incomplete whole GPR phase.
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
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(0x21);
        *reinterpret_cast<signed short*>(OWNER+0xEFA)=0;
    }
    return;
}
