// F863 actual original 0x19E: 122 native B/35 x86/three PE calls.
// Full original fighter switch interior, NOT independent exact CODE.
case 0x19E: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        ClearMotionFields();
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==4 && (animationFrame)==0)
        field07C=1;
    return;
}
