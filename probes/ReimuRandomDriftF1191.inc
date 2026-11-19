case R1191_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1; reinterpret_cast<signed short&>(scriptCounterF00)=0; reinterpret_cast<signed short&>(scriptCounterF02)=0;
        ClearMotionFields();
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) SetAuxActionAt40FB40(R1191_AUX);
    if ((animationStage)==2 && (animationFrame)==0) {
#if R1191_REVERSE_X
        velocityX=g_ReimuReverseDriftAt0065907C-float(SelectRangeAt455580(0,3));
#else
        velocityX=float(SelectRangeAt455580(0,3))+g_ApproachLowerAt00658290;
#endif
        velocityY=float(SelectRangeAt455580(0,R1191_LIFT_RANGE))+g_ReimuRandomLiftAt00657850;
        field05C=0.3f;
    }
    break;
}
