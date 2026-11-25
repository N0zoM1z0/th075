// Youmu's ground recovery and effect 0x33A in action 0x136.
case 0x136: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if ((animationStage)>2 && (velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::One;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    else if (animationStage < animationStageCount) {
        // Continue the current animation.
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnBattleEffect(0x33A,x,y,
            (facing),1);
        PlaySharedSound(0x1D);
    }
    return;
}
