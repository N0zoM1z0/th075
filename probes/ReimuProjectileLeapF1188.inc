case R1188_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f; POS54=0.0f; POS5C=0.0f;
        S16(0x80)=1; I32(0x7C)=0;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        POS=POS-g_ReimuLeapDragAt006583FC;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f; POS54=0.0f; POS5C=0.0f; POS48=0.0f;
            SetAuxActionAt40FB40(10);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x32D,I32(0x44),I32(0x48),*reinterpret_cast<char*>(RAW+0x66),1);
        PlaySoundAt453D40(3);
    }
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=R1188_LEAP_X; POS54=R1188_LEAP_Y; POS5C=0.9f;
        SpawnRawXYAt453C80(0x7F,I32(0x44),I32(0x48),*reinterpret_cast<char*>(RAW+0x66),1);
    }
    if (S16(0x62)==10 && S16(0x64)==0) SetAuxActionAt40FB40(8);
    break;
}
