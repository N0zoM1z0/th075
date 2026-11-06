// Native 198/19E siblings of the earlier 192 projectile policy.
case R1187_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x62)==3 && S16(0x64)==0) {
        F32(0x314)=40.0f; F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(R1187_EFFECT,(*(&F32(0x44)))+g_ThresholdAt0065782C,
            (*(&POS48))+g_ThresholdAt0065782C,*reinterpret_cast<char*>(RAW+0x66),0);
        PlaySoundAt453D40(4);
        StartAnimationAt46D000(250);
    }
    if (S16(0x62)==6 && S16(0x64)==0 && S16(0xF00)<2) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(4);
    }
    break;
}
