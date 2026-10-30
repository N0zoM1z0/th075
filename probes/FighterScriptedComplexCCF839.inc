// F839 real original selected 005214B0 caseCC 428B/126-x86/10 real PE fields.
// Native float evaluation order POS48+POS54 and vtable call OUTSIDE
// conditional stage-short decrement. Genuine direct parent exits.
// Not an independently callable original game function.
case 0xCC: {
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
    if (I16(0x62)==4 && POS54<g_ExtraThresholdAt00657D14)
        SetAuxActionAt40FB40(5);
    ++I16(0x64);
    if (I16(0x64)>=I16(0x72)) {
        I16(0x64)=0;
        ++I16(0x62);
        if (I16(0x62)==3) {
            POS=0.0f;
            POS54=23.0f;
            POS5C=0.75f;
            SpawnRawAt453C80(0x3C,I32(0x44),I32(0x48),1,1);
            FLAG=0;
        }
        if (I16(0x62)>=I16(0x70))
            I16(0x62)=I16(0x62)-2;
        NativeVirtualFrameAdvance();
    }
    return;
}
