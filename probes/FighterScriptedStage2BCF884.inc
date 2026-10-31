// F884 original game 2BC full 803B/228-x86, 22 original physical PE fields.
// Actual double gravity + phases7/9, stage5 FILD+FSUBR and stage8 floatX.
// Two actual native game motion(float,float,int) and full 901B afterRET tables.
// Enclosing 46755B original fighter still NONEXACT, no split case CODE credit.
case 0x2BC: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=0;
        S16(0x80)=1;
        ResetAt453E20();
    }
    if (S16(0x62)>8) {
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
    }
    if (S16(0xF00)==0 && I32(0x7C)!=0) {
        ++S16(0xF00);
        if (I32(0x7C)==1) {
            PrepareActionAt453D40(0xD);
            SpawnExtraAt453B50(0x346,I32(0x44),
                (*(&POS48))+g_ContactProjectionAt00657888,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1,0,1);
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        AnimatePushAt453E80(0x28);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        PrepareActionAt453D60(0x17);
        SpawnAt453C80(0x73,
            reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-
                 float((*reinterpret_cast<signed char*>(RAW+0x66))*64),
            (*(&POS48))+g_F884Stage5YAt00659470,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
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
        SetFloatMotionAt40FBB0(100.0f,60.0f,0);
        F32(0x1C)=3.0f;
        F32(0x20)=0.05f;
        POS=20.0f;
        StartAnimationAt46D000(0x1F4);
        SpawnFloatXRawYAt453C80(0x80,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*150)+F32(0x44),
            I32(0x48),(*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    return;
}
