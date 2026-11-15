// F895 true native action2E4 409B/114x86/11 physical PE fields.
// Real borrowed float distance threshold, random0..4 +2E4 native next state.
// Entire original fighter remains NONEXACT; do not credit interior as callable.
case 0x2E4: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
        ResetAt453E20();
    }
    if ((reinterpret_cast<signed short&>(animationStage))>1 && (reinterpret_cast<signed short&>(animationStage))<10) {
        if (F892AbsAt00412D90(
                reinterpret_cast<FighterBorrowedXViewF833*>(opponent)->xAt44-
                reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44)
                    <g_F895AbsThresholdAt006591F4) {
            SetNativeActionAt40FAC0(RandomBoundaryAt455580(0,4)+0x2E4);
            return;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))>9) {
        velocityX=(velocityX)-g_BounceScaleAt00657F74;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(30,60);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0)
        velocityX=12.5f;
    if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(2);
    }
    return;
}
