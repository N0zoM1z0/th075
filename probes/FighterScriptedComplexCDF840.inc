// F840 original 005214B0 native CD 387 CODE B/113 x86/8 PE fields.
// Stage3 native POS 11, velocity17.5, drag0.8, original vtable call
// outside conditional subtract; native stage3-only FLAG clear.
// Original game interior, not independently callable exact CODE.
case 0xCD: {
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
            POS=11.0f;
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
