// F626: native 109-instruction action0x63 in regular fighter giants.
// Its four action-transition exits return from the parent; the shared
// partial-parent frame/default path must not run after those transitions.
// no bonus-action branch after the +0x32A == 2 mode transition.
// This original natural C++ is distinct from 118-x86 F624 source.
// Not a separately accepted whole function or byte-level code graft.
case 0x63: {
    // Two real short-circuit PE edges: mode != 3 jumps into the
    // stage-two path, while (mode == 3 && this+0x2CD != 0) jumps to
    // the other three action transitions. This is NOT a simple if(mode).
    if (g_ModeAt006714B4 != 3 ||
        field2CD==0) {
        if (animationStage==2 &&
            field39D>0 &&
            opponent->action<150) {
            ResetPrimaryCounters(0x5F);
            field3CF=1;
            return;
        }
    } else {
        if (animationStage>1 &&
            field39D>0 &&
            opponent->action<150 &&
            static_cast<signed char>(field32A[field39D])==2) {
            ResetPrimaryCounters(0x31C);
            // Unlike the special F624 fighter, the actual native
            // stage-two action ends immediately: no bonus offset+0x370.
            return;
        }
        if (animationStage>0 &&
            field39D>0 &&
            opponent->action<150 &&
            static_cast<signed char>(field32A[field39D])==1) {
            ResetPrimaryCounters(0x31C);
            return;
        }
        if (animationStage>1 &&
            field39D>0 &&
            opponent->action<150 &&
            static_cast<signed char>(field32A[field39D])==0) {
            ResetPrimaryCounters(0x5F);
            field3CF=1;
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(2);
    break;
}
