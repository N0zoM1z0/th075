// Original 0045DD70 falling/recovery states 12C..136, continued in the
// live whole-function parent. No state is an independent exact callable.
#define F653_ACTION 0x12C
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 3
#define F653_PREPARE_ANIM 0x1B
#define F653_CLEAR_F00 0
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#define F653_ACTION 0x12D
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 2
#define F653_PREPARE_ANIM 0x1C
#define F653_CLEAR_F00 1
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
case 0x12E: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (S16(0x62)>2 && POS>g_ThresholdAt0065782C) {
        POS=POS-g_AnimationDeltaAt0065747C;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=12.0f;
        if (*reinterpret_cast<unsigned int*>(RAW+0x4E8)>9U) {
            SetNativeActionAt40FAC0(0x136);
            POS=0.0f;
        }
        break;
    }
    if (S16(0x62)==5 && S16(0x64)==0) {
        InitTrajectoryAt453E60(2.0f);
        SpawnFloatXYAt453A70(0x325,
            float(*reinterpret_cast<signed char*>(RAW+0x66)*170)+F32(0x44),
            POS48-g_ApproachLowerAt00658290,
            *reinterpret_cast<char*>(RAW+0x66),0);
    }
    break;
}
case 0x12F: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=6;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x64)==0 && S16(0x62)<12) I32(0x7C)=0;
    if (S16(0x62)==3 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==5 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==7 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==9 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    break;
}
case 0x130: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (POS48>g_ThresholdAt0065782C) POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C && S16(0x62)<12 && S16(0x62)>5) {
        SetAuxActionAt40FB40(12);
        POS48=0.0f; POS5C=0.0f; POS54=0.0f; POS=0.0f;
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=5.0f; POS54=12.5f; POS5C=1.0f; FLAG=0;
        PrepareActionAt453D60(0x1C);
    }
    if (S16(0x62)==12 && S16(0x64)==0) SetAuxActionAt40FB40(11);
    break;
}
case 0x131: {
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        POS48=0.0f; POS5C=0.0f; POS54=0.0f;
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0; S16(0x80)=3; I32(0x7C)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==1 && S16(0x64)==0) PrepareActionAt453D60(0x1B);
    if (S16(0x62)==2 && S16(0x64)==0)
        SpawnFloatXYAt453A70(0x328,
            float(*reinterpret_cast<signed char*>(RAW+0x66)*145)+F32(0x44),
            (*(&POS48))+g_ReimuShotYAt006590A4,*reinterpret_cast<char*>(RAW+0x66),1);
    if (S16(0x62)==4 && S16(0x64)==0 && S16(0xF00)<2) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(2);
        I32(0x7C)=0;
    }
    break;
}
case 0x132: {
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        POS48=0.0f; POS5C=0.0f; POS54=0.0f;
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) { S16(0x80)=1; I32(0x7C)=0; }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==2 && S16(0x64)==0) PrepareActionAt453D60(0x1C);
    break;
}
case 0x133: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f; POS54=0.0f; POS5C=0.0f; S16(0x80)=1; I32(0x7C)=0;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        POS=POS-g_ReimuAirDragAt00658348;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f; POS54=0.0f; POS5C=0.0f; POS48=0.0f;
            SetAuxActionAt40FB40(11);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=10.0f; POS54=8.0f; POS5C=0.8f;
        PrepareActionAt453D60(0x1C);
    }
    break;
}
#define F653_ACTION 0x134
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 4
#define F653_PREPARE_ANIM 0x1C
#define F653_CLEAR_F00 0
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
case 0x135: {
    if (S16(0x62)==0 && S16(0x64)==0) { ResetAt453E20(); S16(0xF00)=0; }
    if (S16(0x62)>4 && POS48==g_ThresholdAt0065782C) {
        POS=POS-g_ReimuGroundDragAt00658350;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (POS48>g_ThresholdAt0065782C) POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C && POS54<g_ThresholdAt0065782C && S16(0x62)==2) {
        SetAuxActionAt40FB40(3);
        POS48=0.0f; POS5C=0.0f; POS54=0.0f;
        PrepareActionAt453D60(0x1D);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
    if (S16(0x62)==2 && S16(0x64)==0) {
        S16(0x80)=1; I32(0x7C)=0; POS=12.0f; POS54=6.0f; POS5C=0.8f;
    }
    // Original 004639D2..00463A2C really nests stage 5 under stage 3.
    // Keep both observed guards; simplifying this contradictory path would
    // discard native instructions rather than reconstruct the original.
    if (S16(0x62)==3 && S16(0x64)==0) {
        if (S16(0x62)==5 && S16(0x64)==0 && S16(0xF00)<4) {
            ++S16(0xF00);
            SetAuxActionAt40FB40(3);
        }
    }
    break;
}
case 0x136: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        FLAG=0; ResetAt453E20(); S16(0x80)=1; I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) { POS=0.0f; FLAG=0; }
    }
    if (S16(0x62)>3 && POS>g_ThresholdAt0065782C) {
        POS=POS-g_ReimuLateDragAt006581E0;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0) { POS=15.0f; PrepareActionAt453D60(0x1D); }
    break;
}
