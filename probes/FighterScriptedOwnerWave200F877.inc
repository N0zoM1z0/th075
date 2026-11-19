// F877 native original 200: complete 634B/177-x86/10 genuine PE call fields.
// Six actual FILD integer temps. Stage5 must FILD then FSUBR ownerX member.
// Genuine borrowed actor X lvalue repairs wrong FISUB source; no code patches.
// Whole original 46755B game function remains NONEXACT.
case 0x200: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=0;
        field07C=0;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        return;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*74)+(x);
    }
    if ((animationStage)==1 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*46)+(x);
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*23)+(x);
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=float((facing)*13)+(x);
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->facing = facing;
        opponent->x=float((facing)*-6)+(x);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        opponent->ResetPrimaryCounters(0x64);
        opponent->x=x-float((facing)*26);
    }
    if ((animationStage)==6 && (animationFrame)==0)
        opponent->ResetPrimaryCounters(0x35);
    return;
}
