// F872 original game 0x1F9, whole 227B/65-x86, original physical fields.
// Stage2 motion3 float X facing*original mult, Y original global, owner+0x82.
// Complete father NONEXACT, no independent case exact CODE.
case 0x1F9: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (S16(0x62)==2 && I32(0x7C)==3) {
        SpawnAt453C80(0x32,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*50)+F32(0x44),
            (*(&POS48))+g_F872Volley1F9YAt006598BC,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(0x14);
        *reinterpret_cast<signed short*>(OWNER+0x82)=0x1E;
        SetNativeActionAt40FAC0(0x1FB);
        return;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    return;
}
