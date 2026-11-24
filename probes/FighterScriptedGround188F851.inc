// F851 real original native 188 214B/61x86/6 PE; naturally shaped stage2.
// F850 current original native actor 0x187 natural falling/animation source.
// Entire original game case, not an independent callable function.
case 0x188: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
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
        ResetPrimaryCounters(2);
    if ((animationStage)==2 && (animationFrame)==0) {
        PlaySharedSound(0x1D);

    }
    return;
}
