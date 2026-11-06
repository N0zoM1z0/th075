// Original Reimu 186..192 attack policies. Interior evidence only;
// the single 0045DD70 owner remains incomplete and NONEXACT.
case 0x186: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (S16(0x62)>3 && POS>g_ThresholdAt0065782C) {
        POS=POS-g_AnimationDeltaAt0065747C;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=15.0f;
        PrepareActionAt453D60(0x1D);
    }
    break;
}
case 0x187: {
    if (S16(0x62)==0 && S16(0x64)==0) S16(0xF00)=0;
    if (S16(0x62)<5 && POS48==g_ThresholdAt0065782C) {
        POS=POS-g_ReimuGroundDragAt00658350;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=9.0f; POS54=0.0f; POS5C=0.0f;
        S16(0x80)=1; I32(0x7C)=0;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f; POS54=0.0f; POS5C=0.0f; POS48=0.0f;
            SetAuxActionAt40FB40(0xB);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=10.0f; POS54=12.5f; POS5C=0.85f;
        PrepareActionAt453D60(0x1C);
    }
    break;
}
case 0x188: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        I32(0x7C)=0;
        POS=8.0f;
    }
    if (S16(0x62)>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=8;
        I32(0x7C)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x64)==0 && S16(0x62)<12) I32(0x7C)=0;
    if (S16(0x62)==3 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==5 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==7 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==9 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    break;
}
case 0x189: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1; I32(0x7C)=0;
        POS=12.0f; FLAG=0;
    }
    if (S16(0x62)==0 && S16(0x64)==0) S16(0xF00)=0;
    if (S16(0x62)>4 && POS48==g_ThresholdAt0065782C) {
        POS=POS-g_ReimuGroundDragAt00658350;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x62)==2 && S16(0x64)==0) {
        S16(0x80)=1; I32(0x7C)=0; POS=12.0f;
    }
    if (S16(0x62)==3 && S16(0x64)==0) PrepareActionAt453D60(0x1D);
    if (S16(0x62)==5 && S16(0x64)==0 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(3);
    }
    break;
}
#define R1186_ACTION 0x190
#define R1186_ANGLE0 -20.0f
#define R1186_ANGLE1 -10.0f
#define R1186_ANGLE2 0.0f
#define R1186_ANGLE3 10.0f
#define R1186_X_OFFSET 114
#define R1186_Y_OFFSET g_ReimuLowVolleyYAt006590A0
#include "ReimuFiveShotAttackF1186.inc"
#undef R1186_ACTION
#undef R1186_ANGLE0
#undef R1186_ANGLE1
#undef R1186_ANGLE2
#undef R1186_ANGLE3
#undef R1186_X_OFFSET
#undef R1186_Y_OFFSET
#define R1186_ACTION 0x191
#define R1186_ANGLE0 60.0f
#define R1186_ANGLE1 50.0f
#define R1186_ANGLE2 40.0f
#define R1186_ANGLE3 30.0f
#define R1186_X_OFFSET 90
#define R1186_Y_OFFSET g_ReimuHighVolleyYAt0065909C
#include "ReimuFiveShotAttackF1186.inc"
#undef R1186_ACTION
#undef R1186_ANGLE0
#undef R1186_ANGLE1
#undef R1186_ANGLE2
#undef R1186_ANGLE3
#undef R1186_X_OFFSET
#undef R1186_Y_OFFSET
case 0x192: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x62)==3 && S16(0x64)==0) {
        F32(0x314)=40.0f; F32(0x318)=10.0f;
        SpawnFloatXYAt453A70(0x338,(*(&F32(0x44)))+g_ThresholdAt0065782C,
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
