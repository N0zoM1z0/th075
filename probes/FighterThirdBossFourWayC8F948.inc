// F948 original pinned Japanese TH075 giant 004AC040 native action 0xC8
// (004B009E..004B02B9): 539 CODE B/149 original x86.
// This genuine natural source has 149 original mnemonic and GPR roles,
// but emits only 529B because the 82KB original saved-this (-0x64)
// and integer-to-x87 signed temporary (-0x94) do not yet have their
// native owner positions in the partial C++ parent (source -0x10/-0x40).
// Three physically wrong x86 widths are NOT to be hidden with padding,
// manual ASM, fake locals, or separate-case 'exact' credit.
case 0xC8: {
    FLAG=1;
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        S16(0xF00)=0;
    }
    if (POS>g_F948_C8UpperAt00657854) {
        POS=POS-g_F948_C8DragAt00658350;
        if (POS<g_F948_C8UpperAt00657854)
            POS=11.0f;
    }
    if (I32(0x4E0)<0) {
        if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
            SetNativeActionAt40FAC0(0xCD);
            break;
        }
        SetNativeActionAt40FAC0(0xCC);
        break;
    }
    if (S16(0xF00)>0 &&
        static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)<=0) {
        SetNativeActionAt40FAC0(0xCF);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0 &&
            S16(0xF00)<2) {
            SetAuxActionAt40FB40(4);
            ++S16(0xF00);
            break;
        }
        SetNativeActionAt40FAC0(0xCF);
        break;
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=14.5f;
        SpawnAt453C80(0x7D,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_F948_C8VolleyYAt00658268,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_F948_C8VolleyYAt00658268,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(31);
    }
    break;
}
