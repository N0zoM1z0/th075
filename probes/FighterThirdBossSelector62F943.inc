// F943: native 004AC040 state0x62 004AE7E2..004AE839,
// 87 original CODE B /25 x86/4 real game-call PE fields.
// Authored as a real internal state in a still NONEXACT 82KB
// original fighter parent; not a standalone game function.
        case 0x62: {
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0x5F);
                if (S16(0xF00)==1)
                    SetNativeActionAt40FAC0(0x5D);
                if (S16(0xF00)==2)
                    SetNativeActionAt40FAC0(0x5E);
            }
            break;
        }
