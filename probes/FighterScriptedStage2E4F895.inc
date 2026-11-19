// F895 true native action2E4 409B/114x86/11 physical PE fields.
// Real borrowed float distance threshold, random0..4 +2E4 native next state.
// Entire original fighter remains NONEXACT; do not credit interior as callable.
case 0x2E4: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=0;
        field080=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
        ResetAt453E20();
    }
    if ((animationStage)>1 && (animationStage)<10) {
        if (F892AbsAt00412D90(
                opponent->x-
                x)
                    <g_F895AbsThresholdAt006591F4) {
            SetNativeActionAt40FAC0(RandomBoundaryAt455580(0,4)+0x2E4);
            return;
        }
    }
    if ((animationStage)>9) {
        velocityX=(velocityX)-g_BounceScaleAt00657F74;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (GetNativeActionAt40FA30()==(field070)) {
        SetNativeActionAt40FAC0(0);
        aiCardTimer=RandomBoundaryAt455580(30,60);
    }
    if ((animationStage)==2 && (animationFrame)==0)
        velocityX=12.5f;
    if ((animationStage)==10 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(2);
    }
    return;
}
