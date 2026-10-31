// F974 original Japanese TH075 004AC040 single-shot 19B/19C.
 // Original each 355B/87 x86/7 genuine typed PE/global fields.
 // Authentic native source +0x314 angle, +0x318 float velocity, sprite
 // 0x326 original call; 19B facing*49 at stage>5 and angle -30;
 // 19C facing*97 at stage>4 and angle +30. Both normal VC7.1
 // sources emit native whole case mnemonic/width but 56 wrong GPR.
 // Entire original 82KB game fighter remains NONEXACT.
// F974 authentic original Japanese 004AC040 action 0x19B, one shot.
case 0x19B: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>5 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4-30);
        F32(0x318)=15.0f;
        SpawnFloatXYAt453A70(0x326,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F974_ShotYAt00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
// F974 authentic original Japanese 004AC040 action 0x19C, one shot.
case 0x19C: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4+30);
        F32(0x318)=15.0f;
        SpawnFloatXYAt453A70(0x326,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F974_ShotYAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
