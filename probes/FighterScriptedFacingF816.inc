// F816 original scripted fighter 005214B0 case0x5F full 144B/44 x86.
 // The physical original exits DIRECTLY to the encompassing native
 // epilogue, not through the default-case internal short JMP. In this
 // void Advance() whose switch is followed only by return, a normal
 // function return reproduces that actual native control-flow target.
 // This case is NOT an independently callable exact original function.
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
    return;
}
