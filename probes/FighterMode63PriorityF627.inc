// F627: actual original 138-instruction action0x63 in two huge
// fighters, with a separate 0x370[index]==5 && 0x32A[index]==2
// priority bonus BEFORE ordinary 0x31C transition. Still only an
// unfinished original giant source case, not a complete exact function.
// Not a separately accepted whole function or byte-level code graft.
case 0x63: {
    // Two real short-circuit PE edges: mode != 3 jumps into the
    // stage-two path, while (mode == 3 && this+0x2CD != 0) jumps to
    // the other three action transitions. This is NOT a simple if(mode).
    if (g_ModeAt006714B4 != 3 ||
        field2CD==0) {
        if (reinterpret_cast<signed short&>(animationStage)==2 &&
            field39D>0 &&
            reinterpret_cast<signed short&>(opponent->action)<150) {
            SetNativeActionAt40FAC0(0x5F);
            field3CF=1;
            break;
        }
    } else {
        // This native 138-x86 owner first checks a bonus action when
        // BOTH +0x370[index] == 5 and +0x32A[index] == 2.
        // The later ordinary +0x32A==2 -> 0x31C branch still exists;
        // this is a separate original C++ early-exit, not a nested
        // optional bonus *after* setting action0x31C.
        if (reinterpret_cast<signed short&>(animationStage)>1 &&
            field39D>0 &&
            reinterpret_cast<signed short&>(opponent->action)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x370+
                field39D)==5 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                field39D)==2) {
            SetNativeActionAt40FAC0(0x303);
            break;
        }
        if (reinterpret_cast<signed short&>(animationStage)>1 &&
            field39D>0 &&
            reinterpret_cast<signed short&>(opponent->action)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                field39D)==2) {
            SetNativeActionAt40FAC0(0x31C);
            // Unlike the special F624 fighter, the actual native
            // stage-two action ends immediately: no bonus offset+0x370.
            break;
        }
        if (reinterpret_cast<signed short&>(animationStage)>0 &&
            field39D>0 &&
            reinterpret_cast<signed short&>(opponent->action)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                field39D)==1) {
            SetNativeActionAt40FAC0(0x31C);
            break;
        }
        if (reinterpret_cast<signed short&>(animationStage)>1 &&
            field39D>0 &&
            reinterpret_cast<signed short&>(opponent->action)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                field39D)==0) {
            SetNativeActionAt40FAC0(0x5F);
            field3CF=1;
            break;
        }
    }
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070))
        SetAuxActionAt40FB40(2);
    break;
}
