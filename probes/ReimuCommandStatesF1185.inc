// Actual original Reimu C8..D0 command/motion states in the whole parent.
// Source-compatible DWORD coordinate views retain original MOV/PUSH transfer.
case 0xC8: {
    FLAG=1;
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) { POS=0.0f; S16(0xF00)=0; }
    if (POS>g_ReimuC8BrakeAt00657D70) {
        POS=POS-g_SubtractAt00657478;
        if (POS<g_ReimuC8ClampAt006590B0) POS=9.0f;
    }
    if (I32(0x4E0)<0) {
        if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
            SetNativeActionAt40FAC0(0xCD);
            break;
        }
        SetNativeActionAt40FAC0(0xCC);
        break;
    }
    if (S16(0xF00)>0 && (*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)<=0) {
        SetNativeActionAt40FAC0(0xCF);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0 && S16(0xF00)<3) {
            SetAuxActionAt40FB40(5);
            ++S16(0xF00);
            break;
        }
        SetNativeActionAt40FAC0(0xCF);
        break;
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=11.0f;
        SpawnAt453C80(0x7D,float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
            (*(&POS48))+g_ReimuCommandYAt00658268,*reinterpret_cast<char*>(RAW+0x66),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),(*(&POS48))+g_ReimuCommandYAt00658268,
            *reinterpret_cast<char*>(RAW+0x66),1);
        PrepareActionAt453D60(31);
    }
    break;
}
case 0xC9: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) POS=0.0f;
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS=-10.0f; POS54=5.0f; POS5C=0.6f;
        SpawnMixedAt453C80(0x7D,I32(0x44),(*(&POS48))+g_ReimuCommandYAt00658268,
            -*reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),(*(&POS48))+g_ReimuCommandYAt00658268,
            -*reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(31);
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>1 && S16(0x62)<5) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f; POS54=0.0f; POS5C=0.0f; POS48=0.0f; S16(0x64)=0;
            SetAuxActionAt40FB40(5);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) SetAuxActionAt40FB40(S16(0x62)-2);
    break;
}
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) { POS=0.0f; POS54=0.0f; POS5C=0.0f; }
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=9.0f; POS54=5.0f; POS5C=0.45f;
        SpawnAt453C80(0x7D,float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
            (*(&POS48))+g_ReimuCommandFrontYAt006590AC,*reinterpret_cast<char*>(RAW+0x66),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),(*(&POS48))+g_ReimuCommandFrontYAt006590AC,
            *reinterpret_cast<char*>(RAW+0x66),1);
        PrepareActionAt453D60(31);
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>1) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f; POS54=0.0f; POS5C=0.0f; POS48=0.0f; S16(0x64)=0;
            SetNativeActionAt40FAC0(10);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(9);
    break;
}
case 0xCB: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) { S16(0xF00)=0; POS=0.0f; POS54=0.0f; POS5C=0.0f; }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>0) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f; POS54=0.0f; POS5C=0.0f; POS48=0.0f; S16(0x64)=0;
            SetNativeActionAt40FAC0(10);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(8);
    if (S16(0x62)==1 && S16(0x64)==0) {
        POS=-9.0f; POS54=5.0f; POS5C=0.45f;
        SpawnMixedAt453C80(0x7D,I32(0x44),(*(&POS48))+g_ReimuCommandBackYAt006590A8,
            -*reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),(*(&POS48))+g_ReimuCommandBackYAt006590A8,
            -*reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(31);
    }
    break;
}
#define R1185_ACTION 0xCC
#define R1185_HAS_AUX 1
#define R1185_X_SPEED 0.0f
#define R1185_Y_SPEED 20.0f
#include "ReimuComplexMotionF1185.inc"
#undef R1185_ACTION
#undef R1185_HAS_AUX
#undef R1185_X_SPEED
#undef R1185_Y_SPEED
#define R1185_ACTION 0xCD
#define R1185_HAS_AUX 1
#define R1185_X_SPEED 9.0f
#define R1185_Y_SPEED 15.0f
#include "ReimuComplexMotionF1185.inc"
#undef R1185_ACTION
#undef R1185_HAS_AUX
#undef R1185_X_SPEED
#undef R1185_Y_SPEED
#define R1185_ACTION 0xCE
#define R1185_HAS_AUX 0
#define R1185_X_SPEED -9.0f
#define R1185_Y_SPEED 15.0f
#include "ReimuComplexMotionF1185.inc"
#undef R1185_ACTION
#undef R1185_HAS_AUX
#undef R1185_X_SPEED
#undef R1185_Y_SPEED
#include "FighterFallStateCFF647.inc"
case 0xD0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        *reinterpret_cast<signed char*>(RAW+0x66)=-*reinterpret_cast<signed char*>(RAW+0x66);
        POS=-POS;
    }
    if (*(&POS5C)==g_ThresholdAt0065782C) POS5C=0.6f;
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        POS48=0.0f;
        ResetAt453E20();
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(4);
    break;
}
