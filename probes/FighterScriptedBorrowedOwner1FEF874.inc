// F874 selected original owner pointer +0x2E8, two native calls and owner X/float Y.
// Native outer equality/inner range forms ONE real conditional with else zero.
// 1FD has true original 6B CMP ECX,149 not yet normal VC7.1-restored.
// Original whole giant NONEXACT, no inner-case callable exact credit.
case 0x1FE: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=0;
        field07C=0;
        field3AC=0;
    }
    if ((animationStage)==2 && field07C==1) {
        SpawnAuxEffect(0x50,
            float((facing)*80)+(x),
            (*(&y))+g_F872Volley1FAYAt00659310,
            (facing),1);
        opponent->ClearMotionFields();
        opponent->ResetPrimaryCounters(0x66);
        opponent->x=float((facing)*80)+(x);
        ResetPrimaryCounters(0x200);
        return;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        if (opponent->y==g_ThresholdAt0065782C &&
           (opponent->action<0x32 ||
            opponent->action>0x95)) {
            field080=1;
        } else {
            field080=0;
        }
    }
    return;
}
