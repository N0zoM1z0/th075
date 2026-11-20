// F620: complete native 44-instruction action0x5F in normal fighter
// giant Advance(), real per-owner action transitions and independent
// x87 direction tests. Case body is NOT a separately accepted function.
case 0x5F: {
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetPrimaryCounters(F620_FIRST_ACTION);
        if (inputY>0)
            ResetPrimaryCounters(F620_SECOND_ACTION);
    }
    if (animationStage==animationStageCount-1) {
        if (*(&x)>opponent->x)
            facing=-1;
        if (*(&x)<opponent->x)
            facing=1;
    }
    break;
}
