// F990 pinned original Japanese 004AC040 action259.
 // Native 004B7EF2..004B823F, 845B/212 x86, 15 original
 // external PE fields. Five sprite0x325 shots with signed
 // facing*100 and genuine FILD/FSUBR original X, F02*3+
 // 145/140/135/130/125 angles. Complete normal VC7.1
 // source generates all 212 native mnemonic roles, but
 // three register-dependent angle ADD widths at native
 // indices34/96/127 and 137 GPR roles remain wrong.
 // Whole original 82KB game callable NONEXACT.
case 0x259: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF02)<3 && S16(0xF00)<=0) {
        PrepareActionAt453D40(0);
        F32(0x314)=float(S16(0xF02)*3+145);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*100),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+140);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*100),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+135);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*100),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+130);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*100),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*3+125);
        F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x325,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*100),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x64);
        ++S16(0xF02);
        S16(0xF00)=3;
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
