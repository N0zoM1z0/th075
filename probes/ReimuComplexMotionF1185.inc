// Native Reimu CC/CD/CE motion loop. Parameters are actual actor policies;
// this source is included only by the live nonexact 0045DD70 parent.
case R1185_ACTION: {
    if ((*(&POS48)==g_ThresholdAt0065782C) || POS54>g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
        S16(0x88)=2;
    }
    if (S16(0x62)==0 && FLAG==0) ResetAt453E20();
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(10);
            POS48=0.0f;
            ResetAt453E20();
            break;
        }
    }
#if R1185_HAS_AUX
    if (S16(0x62)==4 && POS54<g_ExtraThresholdAt00657D14) SetAuxActionAt40FB40(5);
#endif
    ++S16(0x64);
    if (S16(0x64)>=S16(0x72)) {
        S16(0x64)=0;
        ++S16(0x62);
        if (S16(0x62)==2) {
            POS=R1185_X_SPEED;
            POS54=R1185_Y_SPEED;
            POS5C=0.65f;
            FLAG=0;
            SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),1,1);
        }
        if (S16(0x62)>=S16(0x70)) S16(0x62)=S16(0x62)-2;
        NativeVirtualFrameAdvance();
    }
    break;
}
