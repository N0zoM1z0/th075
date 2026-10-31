// F898 original native 2F0 complete 828B/229x86 with mixed float stage/DOUB gravity.
// Full original 46755B parent NONEXACT, not independently callable CODE.
case 0x2F0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        I32(0x7C)=0;
        S16(0x80)=1;
        ResetAt453E20();
    }
    if (S16(0x62)<6) {
        ++S16(0xF02);
        if (S16(0xF02)>4) {
            SpawnAt453C80(0x3E,
                reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-
                    float((*reinterpret_cast<signed char*>(RAW+0x66))*40),
                (*(&POS48))+g_F898ShotYAt0065839C,1,1);
            S16(0xF02)=0;
        }
    }
    if (S16(0x62)>10) {
        POS=POS-g_F884DoubleDropAt00657D00;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (S16(0x62)==7) {
        F32(0x1C)=F32(0x1C)+g_F865SustainScaleAt00658348;
        F32(0x20)=F32(0x20)-g_F884PhaseYAt006598B8;
    }
    if (S16(0x62)==9) {
        F32(0x1C)=F32(0x1C)-g_F865SustainScaleAt00658348;
        F32(0x20)=F32(0x20)+g_F884PhaseYAt006598B8;
        POS=2.0f;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        PrepareActionAt453D40(0xD);
        SpawnWithFloatAt453A70(0x38D,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==7 && S16(0x64)==0) {
        PrepareActionAt453D40(0xA);
        SetFloatMotionAt40FBB0(-200.0f,60.0f,0);
        F32(0x1C)=1.0f;
        F32(0x20)=1.0f;
        *reinterpret_cast<signed char*>(RAW+0x11)=-1;
        *reinterpret_cast<signed char*>(RAW+0x12)=-1;
        *reinterpret_cast<signed char*>(RAW+0x13)=-1;
        *reinterpret_cast<signed char*>(RAW+0x14)=-1;
    }
    if (S16(0x62)==10 && S16(0x64)==0) {
        F32(0x1C)=1.0f;
        F32(0x20)=1.0f;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        S16(0x516)=static_cast<short>(
            static_cast<int>(g_CloudOpponentAt006714D0)*30+240);
        SetFloatMotionAt40FBB0(100.0f,60.0f,0);
        F32(0x1C)=3.0f;
        F32(0x20)=0.05f;
        POS=20.0f;
        SpawnFloatXRawYAt453C80(0x80,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*150)+F32(0x44),
            I32(0x48),(*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==11 && S16(0x64)==0)
        POS=15.0f;
    return;
}
