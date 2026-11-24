// F895 true native action2E4 409B/114x86/11 physical PE fields.
// Real borrowed float distance threshold, random0..4 +2E4 native next state.
// Entire original fighter remains NONEXACT; do not credit interior as callable.
case 0x2E4: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=0;
        field080=1;
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        ClearMotionFields();
    }
    if ((animationStage)>1 && (animationStage)<10) {
        if (AbsFloatAt00412D90(
                opponent->x-
                x)
                    <GeometryConstants::FourHundred) {
            ResetPrimaryCounters(RecordedRange(0,4)+0x2E4);
            return;
        }
    }
    if ((animationStage)>9) {
        velocityX=(velocityX)-FloatConstants::Quarter;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RecordedRange(30,60);
    }
    if ((animationStage)==2 && (animationFrame)==0)
        velocityX=12.5f;
    if ((animationStage)==10 && (animationFrame)==0 && (scriptCounterF00)<2) {
        ++scriptCounterF00;
        ResetSecondaryCounter(2);
    }
    return;
}
