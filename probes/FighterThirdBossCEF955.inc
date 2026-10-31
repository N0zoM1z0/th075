// F955 true original 004AC040 native action CE, 004B0BB8..004B0D42;
// 394 whole interior CODE B /115 x86 /9 genuine external PE fields.
// Genuine 0x3C projectile precedes stage-3 motion values, and
// this action has NO stage-4 auxiliary-speed test (unlike CC/CD).
// Natural case is embedded only in the still NONEXACT 82KB parent.
case 0xCE: {
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
    ++I16(0x64);
    if (I16(0x64)>=I16(0x72)) {
        I16(0x64)=0;
        ++I16(0x62);
        if (I16(0x62)==3) {
            // Original native call before the actual motion values are reset.
            SpawnRawAt453C80(0x3C,I32(0x44),I32(0x48),1,1);
            POS=-10.0f;
            POS54=15.0f;
            POS5C=0.7f;
            FLAG=0;
        }
        if (I16(0x62)>=I16(0x70))
            I16(0x62)=I16(0x62)-2;
        NativeVirtualFrameAdvance();
    }
    break;
}
