// F996 native Japanese TH075 original 004AC040 state25C.
 // Real original PE 004B9327..004B973A: 1043 CODE B /271 x86,
 // 23 original typed PE external fields, nine genuine sprite342
 // shots with angles -28,-21,-14,-7,0,+7,+14,+21,+28.
 // All original mnemonic/width roles match normal VC7.1 source,
 // 162 GPR positions differ, whole 82KB original NONEXACT.
// F996 original Japanese fighter 004AC040 native action25C.
case 0x25C: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    --S16(0xF00);
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0xFA);
        F32(0x314)=-28.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=-21.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=-14.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=-7.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=0.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=7.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=14.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=21.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=28.0f;
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    break;
}
