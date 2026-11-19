// Actual original Reimu C8..D0 command/motion states in the whole parent.
// Source-compatible DWORD coordinate views retain original MOV/PUSH transfer.
case 0xC8: {
    field3AC=1;
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) { velocityX=0.0f; scriptCounterF00=0; }
    if ((velocityX)>g_ReimuC8BrakeAt00657D70) {
        velocityX=(velocityX)-g_SubtractAt00657478;
        if ((velocityX)<g_ReimuC8ClampAt006590B0) velocityX=9.0f;
    }
    if (inputY<0) {
        if ((facing)*inputX>0) {
            ResetPrimaryCounters(0xCD);
            break;
        }
        ResetPrimaryCounters(0xCC);
        break;
    }
    if ((scriptCounterF00)>0 && (facing)*inputX<=0) {
        ResetPrimaryCounters(0xCF);
        break;
    }
    if (AdvanceNestedFrame()==(field070)) {
        if ((facing)*inputX>0 && (scriptCounterF00)<3) {
            ResetSecondaryCounter(5);
            ++scriptCounterF00;
            break;
        }
        ResetPrimaryCounters(0xCF);
        break;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=11.0f;
        SpawnAuxEffect(0x7D,float(facing*80)+(x),
            (*(&y))+g_ReimuCommandYAt00658268,reinterpret_cast<char&>(facing),1);
        SpawnAuxEffect(0x7E,x,(*(&y))+g_ReimuCommandYAt00658268,
            reinterpret_cast<char&>(facing),1);
        PlaySharedSound(31);
    }
    break;
}
case 0xC9: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) velocityX=0.0f;
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=-10.0f; velocityY=5.0f; field05C=0.6f;
        SpawnAuxEffect(0x7D,x,(*(&y))+g_ReimuCommandYAt00658268,
            -facing,1);
        SpawnAuxEffect(0x7E,x,(*(&y))+g_ReimuCommandYAt00658268,
            -facing,1);
        PlaySharedSound(31);
    }
    if (y>g_ThresholdAt0065782C && (animationStage)>1 && (animationStage)<5) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f; animationFrame=0;
            ResetSecondaryCounter(5);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) ResetSecondaryCounter((animationStage)-2);
    break;
}
case 0xCA: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) { velocityX=0.0f; velocityY=0.0f; field05C=0.0f; }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=9.0f; velocityY=5.0f; field05C=0.45f;
        SpawnAuxEffect(0x7D,float(facing*80)+(x),
            (*(&y))+g_ReimuCommandFrontYAt006590AC,reinterpret_cast<char&>(facing),1);
        SpawnAuxEffect(0x7E,x,(*(&y))+g_ReimuCommandFrontYAt006590AC,
            reinterpret_cast<char&>(facing),1);
        PlaySharedSound(31);
    }
    if (y>g_ThresholdAt0065782C && (animationStage)>1) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f; animationFrame=0;
            ResetPrimaryCounters(10);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) ResetSecondaryCounter(9);
    break;
}
case 0xCB: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) { scriptCounterF00=0; velocityX=0.0f; velocityY=0.0f; field05C=0.0f; }
    if (y>g_ThresholdAt0065782C && (animationStage)>0) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f; animationFrame=0;
            ResetPrimaryCounters(10);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) ResetSecondaryCounter(8);
    if ((animationStage)==1 && (animationFrame)==0) {
        velocityX=-9.0f; velocityY=5.0f; field05C=0.45f;
        SpawnAuxEffect(0x7D,x,(*(&y))+g_ReimuCommandBackYAt006590A8,
            -facing,1);
        SpawnAuxEffect(0x7E,x,(*(&y))+g_ReimuCommandBackYAt006590A8,
            -facing,1);
        PlaySharedSound(31);
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
    if ((animationStage)==0 && (animationFrame)==0) {
        facing=-facing;
        velocityX=-(velocityX);
    }
    if (*(&field05C)==g_ThresholdAt0065782C) field05C=0.6f;
    velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        ResetPrimaryCounters(10);
        y=0.0f;
        ClearMotionFields();
        break;
    }
    if (AdvanceNestedFrame()==(field070)) ResetSecondaryCounter(4);
    break;
}
