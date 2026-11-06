case R1189_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        --U8(0x366);
        ResetAt453E20();
        S16(0x80)=1; I32(0x7C)=0; FLAG=0; S16(0xF00)=0;
    }
#if R1189_HAS_BONUS
    if (S16(0x3B6)==0 && I32(0x7C)==1) S16(0x3B0)=1000;
#endif
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),(*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<char*>(RAW+0x66),1);
        PrepareActionAt453D60(0x21);
        *reinterpret_cast<short*>(OWNER+0xEFA)=0;
    }
    break;
}
