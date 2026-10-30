// F834 physical original 005214B0 interior action 0xC8,
 // 657 CODE B /190 x86 and 17 actual typed PE/global fields.
 // Prefix ++ on the real +0xF00 signed short naturally emits
 // original MOV CX/ADD CX,1 instead of MOVSX ECX/ADD ECX,1.
 // All 7 direct returns target the enclosing full fighter epilogue.
 // This is NOT independently callable original exact CODE.
case 0xC8: {
    ConfigureStormAt454BC0(3,4,0xFF);
    FLAG=1;
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        S16(0xF00)=0;
    }
    if (POS>g_F834_UpperAt00657CBC) {
        POS=POS-g_SubtractAt00657478;
        if (POS<g_F834_LowerAt006590B0)
            POS=9.0f;
    }
    if (I32(0x4E0)<0) {
        if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
            SetNativeActionAt40FAC0(0xCD);
            return;
        }
        SetNativeActionAt40FAC0(0xCC);
        return;
    }
    if (S16(0xF00)>0 || S16(0x62)>5) {
        if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)<=0) {
            SetNativeActionAt40FAC0(0xCF);
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
            if (S16(0xF00)<1) {
                SetAuxActionAt40FB40(2);
                ++S16(0xF00);
                return;
            }
        }
        SetNativeActionAt40FAC0(0xCF);
        return;
    }
    if (S16(0x64)==0 &&
            (*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)<=0 &&
            S16(0xF00)>0) {
        SetNativeActionAt40FAC0(0xCF);
        return;
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS=11.5f;
        SpawnAt453C80(0x7D,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D40(15);
    if (S16(0x62)==8 && S16(0x64)==0)
        PrepareActionAt453D40(16);
    return;
}
