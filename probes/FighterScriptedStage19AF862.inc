// F862 physical original 19A 302B/86 x86/eight typed PE fields.
// No stage-zero/reset prefix: adding it makes an INVALID 332B/96x86
// function interior while deceptively making last 302B match GPRs.
// Real ground fall, sprite352 facing*60, stage5 motion, stage6 flag.
case 0x19A: {
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        POS48=0.0f;
        POS5C=0.0f;
        POS54=0.0f;
        return;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x352,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0xC8);
        PrepareActionAt453D40(3);
        POS=-5.0f;
        POS54=12.0f;
        POS5C=0.65f;
    }
    if (S16(0x62)==6 && S16(0x64)==0)
        I32(0x7C)=1;
    return;
}
