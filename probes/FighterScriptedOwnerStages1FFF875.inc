// F875 native original 1FF complete real stage1..6 associated owner action.
// Five actual native FILD scratch slots; original owner+0x44 x87 updates.
// Enclosing 46755B whole fighter still not exact; no inner exact credit.
case 0x1FF: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=0;
        field07C=0;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==1 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*74)+(x);
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*40)+(x);
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*36)+(x);
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*33)+(x);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*32)+(x);
    }
    if ((animationStage)==6 && (animationFrame)==0)
        opponent->ResetPrimaryCounters(0x35);
    return;
}
