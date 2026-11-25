// F941: true independently decoded 004AC040 native 0x5F state
// 004AE300..004AE390: 144 native CODE B/44 x86/3 typed original PE fields.
// This reuses the confirmed F762 real battle-facing semantics with the
// independently confirmed original 004AC040 receiver/opponent +0x44.
// The natural C++ inside a still-PARTIAL 82KB parent has the real
// 0x5F native 44-instruction GPR/mnemonic/width sequence; the original
// entire callable game giant and saved this EBP layout remain NONEXACT.
// Both fighters share the Actor::x member at +0x44.
        case 0x5F: {
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(animationStageCount)-1) {
                if (x >
                    opponent->x)
                    facing=-1;
                if (x <
                    opponent->x)
                    facing=1;
            }
            break;
        }
