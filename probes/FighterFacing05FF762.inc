// F762: actual original action 05F in 00543210. Original GPR phase still NONEXACT;
// normal game source; no independent callable CODE credit.
// Original complete action 05F inside the 58,294-byte authored fighter.
// Observed borrowed float X members in both actors; not new owner instances.
        case 0x5F: {
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(field070)-1) {
                if (x >
                    opponent->x)
                    facing=-1;
                if (x <
                    opponent->x)
                    facing=1;
            }
            break;
        }
