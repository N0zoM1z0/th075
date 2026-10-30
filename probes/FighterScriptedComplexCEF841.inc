// F841 selected original actor 0xCE native 387B/113 x86/8 real PE fields.
// Distinct stage3 native -11.0f X, +17.5f velocity, +0.8f drag.
// Real unconditional virtual frame method, native x87 operand order.
// Interior case only, no independently callable exact CODE.
case 0xCE: {
    if (POS48==g_ThresholdAt0065782C || POS54>g_ThresholdAt0065782C) {
        SetupCollisionAt454BC0(3,4,0xFF);
        I16(0x88)=2;
    }
    if (I16(0x62)==0 && FLAG==0)
        ResetAt453E20();
    if (I16(0x62)>2) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            POS48=0.0f;
            ResetAt453E20();
            return;
        }
    }
    ++I16(0x64);
    if (I16(0x64)>=I16(0x72)) {
        I16(0x64)=0;
        ++I16(0x62);
        if (I16(0x62)==3) {
            POS=-11.0f;
            POS54=17.5f;
            POS5C=0.8f;
            SpawnRawAt453C80(0x3C,I32(0x44),I32(0x48),1,1);
            FLAG=0;
        }
        if (I16(0x62)>=I16(0x70))
            I16(0x62)=I16(0x62)-2;
        NativeVirtualFrameAdvance();
    }
    return;
}
