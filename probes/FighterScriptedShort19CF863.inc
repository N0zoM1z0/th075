// F863 actual original 0x19C: 122 native B/35 x86/three PE calls.
// Full original fighter switch interior, NOT independent exact CODE.
case 0x19C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0)
        field07C=1;
    return;
}
