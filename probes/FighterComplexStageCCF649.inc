// F649 original-native source grammar NEGATIVE: complete stage/collision/
// spawning case0xCC instruction geometry, NOT original GPR/CFG phase.
// Raw sprite x/y arguments are bit-preserving 32-bit ABI source proxies,
// NOT independently established historical game API declarations.
// Whole original giant remains NONEXACT; do not adopt case as exact.
case 0xCC: {
    if ((*(&POS48) == g_ThresholdAt0065782C) ||
        POS54 > g_ThresholdAt0065782C) {
        SetupCollisionAt454BC0(3,4,0xFF);
        I16(0x88)=2;
    }
    if (I16(0x62)==0 && FLAG==0)
        ResetAt453E20();
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(10);
            POS48=0.0f;
            ResetAt453E20();
            break;
        }
    }
    if (I16(0x62)==F649_STAGE_LIMIT &&
        POS54<g_ExtraThresholdAt00657D14)
        SetAuxActionAt40FB40(F649_AUX);
    ++I16(0x64);
    if (I16(0x64)>=I16(0x72)) {
        I16(0x64)=0;
        ++I16(0x62);
        if (I16(0x62)==F649_TRIGGER) {
            POS=F649_POS;
            POS54=F649_SPEED;
            POS5C=F649_DRAG;
#if F649_CLEAR_FLAG
            FLAG=0;
#endif
        }
        // The actual PE pushes raw member bits, not FLD/FSTP arguments.
        SpawnRawAt453C80(0x3C,I32(0x44),I32(0x48),1,1);
        if (I16(0x62)>=I16(0x70)) {
            I16(0x62)=I16(0x62)-2;
            NativeVirtualFrameAdvance();
        }
    }
    break;
}
