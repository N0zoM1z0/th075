// Actual original Reimu C8..D0 command/motion states in the whole parent.
// Source-compatible DWORD coordinate views retain original MOV/PUSH transfer.
case 0xC8: {
    field3AC=1;
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) { velocityX=0.0f; scriptCounterF00=0; }
    if ((velocityX)>GeometryConstants::Eight) {
        velocityX=(velocityX)-FloatConstants::Half;
        if ((velocityX)<GeometryConstants::Nine) velocityX=9.0f;
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
    if (AdvanceNestedFrame()==(animationStageCount)) {
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
            (*(&y))+GeometryConstants::Eighty,facing,1);
        SpawnAuxEffect(0x7E,x,(*(&y))+GeometryConstants::Eighty,
            facing,1);
        PlaySharedSound(31);
    }
    break;
}
case 0xC9: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) velocityX=0.0f;
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=-10.0f; velocityY=5.0f; verticalAcceleration=0.6f;
        SpawnAuxEffect(0x7D,x,(*(&y))+GeometryConstants::Eighty,
            -facing,1);
        SpawnAuxEffect(0x7E,x,(*(&y))+GeometryConstants::Eighty,
            -facing,1);
        PlaySharedSound(31);
    }
    if (y>FloatConstants::Zero && (animationStage)>1 && (animationStage)<5) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f; velocityY=0.0f; verticalAcceleration=0.0f; y=0.0f; animationFrame=0;
            ResetSecondaryCounter(5);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) ResetSecondaryCounter((animationStage)-2);
    break;
}
case 0xCA: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) { velocityX=0.0f; velocityY=0.0f; verticalAcceleration=0.0f; }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=9.0f; velocityY=5.0f; verticalAcceleration=0.45f;
        SpawnAuxEffect(0x7D,float(facing*80)+(x),
            (*(&y))+GeometryConstants::HundredTen,facing,1);
        SpawnAuxEffect(0x7E,x,(*(&y))+GeometryConstants::HundredTen,
            facing,1);
        PlaySharedSound(31);
    }
    if (y>FloatConstants::Zero && (animationStage)>1) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f; velocityY=0.0f; verticalAcceleration=0.0f; y=0.0f; animationFrame=0;
            ResetPrimaryCounters(10);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(9);
    break;
}
case 0xCB: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) { scriptCounterF00=0; velocityX=0.0f; velocityY=0.0f; verticalAcceleration=0.0f; }
    if (y>FloatConstants::Zero && (animationStage)>0) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f; velocityY=0.0f; verticalAcceleration=0.0f; y=0.0f; animationFrame=0;
            ResetPrimaryCounters(10);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(8);
    if ((animationStage)==1 && (animationFrame)==0) {
        velocityX=-9.0f; velocityY=5.0f; verticalAcceleration=0.45f;
        SpawnAuxEffect(0x7D,x,(*(&y))+GeometryConstants::HundredTwenty,
            -facing,1);
        SpawnAuxEffect(0x7E,x,(*(&y))+GeometryConstants::HundredTwenty,
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
#include "characters/shared/actions/FighterFallStateCFF647.inc"
case 0xD0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        facing=-facing;
        velocityX=-(velocityX);
    }
    if (*(&verticalAcceleration)==FloatConstants::Zero) verticalAcceleration=0.6f;
    velocityY=velocityY-verticalAcceleration;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(10);
        y=0.0f;
        ClearMotionFields();
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(4);
    break;
}
