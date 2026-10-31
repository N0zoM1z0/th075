// F895 true native action2E4 409B/114x86/11 physical PE fields.
// Real borrowed float distance threshold, random0..4 +2E4 native next state.
// Entire original fighter remains NONEXACT; do not credit interior as callable.
case 0x2E4: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=0;
        S16(0x80)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        ResetAt453E20();
    }
    if (S16(0x62)>1 && S16(0x62)<10) {
        if (F892AbsAt00412D90(
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-
                reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44)
                    <g_F895AbsThresholdAt006591F4) {
            SetNativeActionAt40FAC0(RandomBoundaryAt455580(0,4)+0x2E4);
            return;
        }
    }
    if (S16(0x62)>9) {
        POS=POS-g_BounceScaleAt00657F74;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(30,60);
    }
    if (S16(0x62)==2 && S16(0x64)==0)
        POS=12.5f;
    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<2) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(2);
    }
    return;
}
