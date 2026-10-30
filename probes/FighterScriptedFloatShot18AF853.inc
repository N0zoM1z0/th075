// F853 selected native 18A: 250B/71x86/6 typed PE fields.
// Genuine float Y left lvalue preserves original x87 width/order.
// Incomplete giant source: original GPR and final-JMP differences remain.
case 0x18A: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=15.0f;
        S16(0xF00)=0;
    }
    POS=POS-g_JumpGroundCorrectionAt00658058;
    if (POS<g_ThresholdAt0065782C) {
        POS=0.0f;
        FLAG=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0)
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*151)+F32(0x44),
            (*(&POS48))+g_F853OffsetYAt0065929C,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    return;
}
