// F953 original Japanese TH075 giant 004AC040 action 0xCC native
// 435 complete inner CODE B /128 x86 and 11 true original typed
// PE external fields; this is NOT an independent whole function.
// Real state transition fires raw 0x3C projectile BEFORE writing
// the new frame/trajectory values. Full 82KB parent remains NONEXACT.
case 0xCC: {
    if ((*(&POS48) == g_ThresholdAt0065782C) ||
        POS54 > g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
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
    if (I16(0x62)==4 &&
        POS54<g_ExtraThresholdAt00657D14)
        SetAuxActionAt40FB40(5);
    ++I16(0x64);
    if (I16(0x64)>=I16(0x72)) {
        I16(0x64)=0;
        ++I16(0x62);
        if (I16(0x62)==3) {
            // Original native call before the actual motion values are reset.
            SpawnRawAt453C80(0x3C,I32(0x44),I32(0x48),1,1);
            POS=0.0f;
            POS54=20.0f;
            POS5C=0.7f;
            FLAG=0;
        }
        if (I16(0x62)>=I16(0x70))
            I16(0x62)=I16(0x62)-2;
        NativeVirtualFrameAdvance();
    }
    break;
}
