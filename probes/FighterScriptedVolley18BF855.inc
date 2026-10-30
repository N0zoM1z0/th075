// F855 native original 18B: 353B/99 x86/7 physical PE fields.
// Real prefix 16-bit ++, stage7 aux6 and stage6 facing*128 FILD.
// Incomplete giant register allocation remains nonnative; no case exact credit.
case 0x18B: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=10.0f;
        S16(0xF00)=0;
    }
    if (S16(0x62)>6) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==7 && S16(0x64)==0 && S16(0xF00)<2) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(6);
    }
    S16(0x80)=1;
    I32(0x7C)=0;
    if (S16(0x62)==6 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*128)+F32(0x44),
            (*(&POS48))+g_F855ShotYAt00658400,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    return;
}
