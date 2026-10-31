// F888 real original game 0x2C0 stage1, true real 453B50 sprite345.
// F10=420 guard is stage>10 for 2C0 but ONLY getter match for 2C1.
// Full 46755B giant NONEXACT, do not treat original inner case as callable CODE.
case 0x2C0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=0;
        S16(0x80)=1;
        ResetAt453E20();
    }
    if (S16(0x62)==1 && S16(0x64)==0) {
        AnimatePushAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        PrepareActionAt453D40(8);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnMixedAt453C80(0x73,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)>10)
        S16(0xF10)=0x1A4;
    if (GetNativeActionAt40FA30()==S16(0x70)) {

        SetNativeActionAt40FAC0(0);
        SpawnExtraAt453B50(0x345,I32(0x44),
        (*(&POS48))+g_ContactProjectionAt00657888,1,1,0,1);
    }
    return;
}
