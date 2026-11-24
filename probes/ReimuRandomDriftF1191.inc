case R1191_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1; scriptCounterF00=0; scriptCounterF02=0;
        ClearMotionFields();
    }
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(R1191_AUX);
    if ((animationStage)==2 && (animationFrame)==0) {
#if R1191_REVERSE_X
        velocityX=GeometryConstants::NegativeSix-float(RecordedRange(0,3));
#else
        velocityX=float(RecordedRange(0,3))+GeometryConstants::Six;
#endif
        velocityY=float(RecordedRange(0,R1191_LIFT_RANGE))+FloatConstants::Ten;
        field05C=0.3f;
    }
    break;
}
