// F870 original native 1F8 complete 469B/143-x86/15 physical PE fields.
// Native FUCOMPP requires bare POS48==global, generating FLD global then FLD member.
// Actual x87 ground contact, stage3 sprite7F, stage7 sprite335, stage15 auxE.
// Full original giant remains register and two-final-JMP NONEXACT.
case 0x1F8: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        if (POS48==g_ThresholdAt0065782C) {
            POS=POS-g_JumpGroundCorrectionAt00658058;
            if (POS<g_ThresholdAt0065782C)
                POS=0.0f;
        }
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xF);
            POS48=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=8.0f;
        POS54=12.0f;
        POS5C=0.8f;
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==7 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x335,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(4);
    }
    if (S16(0x62)==0xF && S16(0x64)==0)
        SetAuxActionAt40FB40(0xE);
    return;
}
