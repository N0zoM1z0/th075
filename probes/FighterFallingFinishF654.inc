// Native fighter 00543210 action 0x12F: separate early/late falling drag.
// Source is part of the still-nonexact whole fighter Advance() C++ TU.
case 0x12F: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0 && S16(0x62)<4) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (S16(0x62)>3) {
        POS=POS-g_FallingLateDragAt00659240;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=25.0f;
        PrepareActionAt453D60(0x1D);
    }
    break;
}
// Original 0x130: ground contact, motion reset, and stage-3 projectile.
case 0x130: {
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        POS48=0.0f;
        POS5C=0.0f;
        POS54=0.0f;
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==3 && S16(0x64)==0) PrepareActionAt453D60(0x1D);
    if (S16(0x62)==3 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x339,I32(0x44),I32(0x48),
                *reinterpret_cast<signed char*>(RAW+0x66),1);
    break;
}
