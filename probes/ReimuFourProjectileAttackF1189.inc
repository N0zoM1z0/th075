case R1189_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
#if R1189_AIR
        POS=POS*g_BounceScaleAt00657F74;
        POS54=(*(&POS54))*g_BounceScaleAt00657F74;
        I32(0x7C)=1;
#else
        I32(0x7C)=1;
        ResetAt453E20();
#endif
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(R1189_NEXT_ACTION);
    if (S16(0x62)==R1189_FIRE_STAGE && S16(0x64)==0) {
        F32(0x314)=0.0f;
        F32(0x318)=(*(&POS48))+R1189_Y_OFFSET;
        SpawnFloatXYAt453A70(R1189_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1189_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1189_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
        F32(0x314)=1.0f;
        SpawnFloatXYAt453A70(R1189_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1189_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1189_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
        F32(0x314)=2.0f;
        SpawnFloatXYAt453A70(R1189_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1189_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1189_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
        F32(0x314)=3.0f;
        SpawnFloatXYAt453A70(R1189_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1189_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1189_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
        StartAnimationAt46D000(250);
        PlaySoundAt453D40(4);
    }
    break;
}
