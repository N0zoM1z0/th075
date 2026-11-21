case R1191_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1; scriptCounterF00=0; scriptCounterF02=0;
        ClearMotionFields();
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(R1191_AUX);
    if ((animationStage)==2 && (animationFrame)==0) {
#if R1191_REVERSE_X
        velocityX=g_ReimuReverseDriftAt0065907C-float(RecordedRange(0,3));
#else
        velocityX=float(RecordedRange(0,3))+g_ApproachLowerAt00658290;
#endif
        velocityY=float(RecordedRange(0,R1191_LIFT_RANGE))+g_ReimuRandomLiftAt00657850;
        field05C=0.3f;
    }
    break;
}
