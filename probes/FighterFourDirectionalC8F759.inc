// F759 real original game action 0xC8..0xCB, all under the same 00543210 giant.
// These are switch-case interiors, not individually accepted callable CODE.
case 0xC8: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        scriptCounterF00=0;
    }
    if (y>FloatConstants::Zero && (animationStage)<7) {
        velocityY=velocityY-FloatConstants::TwoAndHalf;
        if (y+velocityY<=FloatConstants::Zero) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(7);
            break;
        }
    }
    if ((animationStage)==7 && inputY<0) {
        if ((facing)*inputX>0) {
            ResetPrimaryCounters(0xCD);
            break;
        }
        ResetPrimaryCounters(0xCC);
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        break;
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=15.0f;
        velocityY=25.0f;
        verticalAcceleration=2.5f;
        SpawnAuxEffect(0x7D,float((facing)*80)+(x),
            (*(&y))+GeometryConstants::Eighty,(facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Eighty,(facing),1);
        SpawnAuxEffect(0x81,x,0.0f,(facing),0);
        PlaySharedSound(31);
    }
    break;
}
case 0xC9: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        scriptCounterF00=0;
    }
    if (y>FloatConstants::Zero && (animationStage)<6) {
        velocityY=velocityY-GeometryConstants::Six;
        if (y+velocityY<=FloatConstants::Zero) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(6);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        break;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=-25.0f;
        velocityY=40.0f;
        verticalAcceleration=6.0f;
        SpawnAuxEffect(0x7D,x-float((facing)*80),
            (*(&y))+GeometryConstants::Eighty,-(facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Eighty,-(facing),1);
        SpawnAuxEffect(0x81,x,0.0f,-(facing),0);
        PlaySharedSound(31);
    }
    break;
}
case 0xCA: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) ClearMotionFields();
    if (y>FloatConstants::Zero && (animationStage)>5) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f;
            velocityY=0.0f;
            verticalAcceleration=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=30.0f;
        velocityY=-4.0f;
        verticalAcceleration=0.6f;
        SpawnAuxEffect(0x7D,float((facing)*80)+(x),
            (*(&y))+GeometryConstants::Hundred,(facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Hundred,(facing),1);
        PlaySharedSound(31);
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        velocityX=10.0f;
        velocityY=-4.0f;
    }
    break;
}
case 0xCB: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) ClearMotionFields();
    if (y>FloatConstants::Zero && (animationStage)>4) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f;
            velocityY=0.0f;
            verticalAcceleration=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=-30.0f;
        velocityY=2.0f;
        verticalAcceleration=0.6f;
        SpawnAuxEffect(0x7D,x-float((facing)*80),
            (*(&y))+GeometryConstants::Hundred,-(facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Hundred,-(facing),1);
        PlaySharedSound(31);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=-10.0f;
        velocityY=2.0f;
    }
    break;
}
