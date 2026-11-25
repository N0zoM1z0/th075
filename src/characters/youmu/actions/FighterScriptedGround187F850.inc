// F850 current original native actor 0x187 natural falling/animation source.
// Entire original game case, not an independent callable function.
case 0x187: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
        velocityX=12.5f;
    }
    if ((animationStage)>0) {
        velocityX=(velocityX)-FloatConstants::FourFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        PlaySharedSound(0x1C);

    }
    return;
}
