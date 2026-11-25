// F874 selected original owner pointer +0x2E8, two native calls and owner X/float Y.
// Native outer equality/inner range forms ONE real conditional with else zero.
// 1FD has true original 6B CMP ECX,149 not yet normal VC7.1-restored.
// Original whole giant NONEXACT, no inner-case callable exact credit.
case 0x1FD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        remainingHits=0;
        collisionResult=0;
        field3AC=0;
    }
    if ((animationStage)==2 && collisionResult==1) {
        SpawnAuxEffect(0x50,
            float((facing)*80)+(x),
            (*(&y))+GeometryConstants::FortyOne,
            (facing),1);
        opponent->ResetPrimaryCounters(0x66);
        opponent->ClearMotionFields();
        opponent->x=float((facing)*80)+(x);
        ResetPrimaryCounters(0x1FF);
        return;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        if (opponent->y==FloatConstants::Zero &&
           (opponent->action<0x32 ||
            opponent->action>0x95)) {
            remainingHits=1;
        } else {
            remainingHits=0;
        }
    }
    return;
}
