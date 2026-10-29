// F624: selected original 118-instruction action0x63 per-fighter
// event/state machine inside a huge incomplete Advance() whole TU.
// Actual original mode/owner/collision fields, and bonus ID differ.
// Not a separately accepted whole function or byte-level code graft.
case 0x63: {
    // Two real short-circuit PE edges: mode != 3 jumps into the
    // stage-two path, while (mode == 3 && this+0x2CD != 0) jumps to
    // the other three action transitions. This is NOT a simple if(mode).
    if (g_ModeAt006714B4 != 3 ||
        *reinterpret_cast<signed char*>(RAW+0x2CD)==0) {
        if (I16(0x62)==2 &&
            *reinterpret_cast<signed char*>(RAW+0x39D)>0 &&
            *reinterpret_cast<signed short*>(OWNER+0x60)<150) {
            SetNativeActionAt40FAC0(0x5F);
            *reinterpret_cast<signed char*>(RAW+0x3CF)=1;
            break;
        }
    } else {
        if (I16(0x62)>1 &&
            *reinterpret_cast<signed char*>(RAW+0x39D)>0 &&
            *reinterpret_cast<signed short*>(OWNER+0x60)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                *reinterpret_cast<signed char*>(RAW+0x39D))==2) {
            SetNativeActionAt40FAC0(0x31C);
            if (*reinterpret_cast<signed char*>(RAW+0x370+
                *reinterpret_cast<signed char*>(RAW+0x39D))==F624_BONUS_FLAG)
                SetNativeActionAt40FAC0(F624_BONUS_ACTION);
            // Native x86 exits this entire case even without bonus;
            // falling through to the next check is behaviorally wrong.
            break;
        }
        if (I16(0x62)>0 &&
            *reinterpret_cast<signed char*>(RAW+0x39D)>0 &&
            *reinterpret_cast<signed short*>(OWNER+0x60)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                *reinterpret_cast<signed char*>(RAW+0x39D))==1) {
            SetNativeActionAt40FAC0(0x31C);
            break;
        }
        if (I16(0x62)>1 &&
            *reinterpret_cast<signed char*>(RAW+0x39D)>0 &&
            *reinterpret_cast<signed short*>(OWNER+0x60)<150 &&
            *reinterpret_cast<signed char*>(RAW+0x32A+
                *reinterpret_cast<signed char*>(RAW+0x39D))==0) {
            SetNativeActionAt40FAC0(0x5F);
            *reinterpret_cast<signed char*>(RAW+0x3CF)=1;
            break;
        }
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(2);
    break;
}
