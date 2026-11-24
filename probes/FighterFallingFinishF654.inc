// Native fighter 00543210 action 0x12F: separate early/late falling drag.
// Source is part of the still-nonexact whole fighter Advance() C++ TU.
case 0x12F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0 && (animationStage)<4) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if ((animationStage)>3) {
        velocityX=(velocityX)-FloatConstants::NineTenths;
        if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(2);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=25.0f;
        PlaySharedSound(0x1D);
    }
    break;
}
// Original 0x130: ground contact, motion reset, and stage-3 projectile.
case 0x130: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(10);
        y=0.0f;
        field05C=0.0f;
        velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==3 && (animationFrame)==0) PlaySharedSound(0x1D);
    if ((animationStage)==3 && (animationFrame)==0)
        SpawnBattleEffect(0x339,x,y,
                facing,1);
    break;
}
