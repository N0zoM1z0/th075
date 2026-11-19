// F681: genuine original physical terminal 31B, 74 x86 /248 CODE B.
// In the selected whole parent with real 2F0/2F1 and 2F8 source this
// native case becomes context-strict (8 authentic typed REL32 fields).
// Actual saved-this role is source EBP-0xC, original PE EBP-0x44.
        case 0x31B: {
            if ((animationStage)==0 && (animationFrame)==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                BeginFadeParameters(0);
                SelectResourceParameters();
                PlaySharedSound(0x17);
                SpawnBattleEffect(0x3E5,x,y,
                        facing,1);
            }
            if ((animationStage)==11 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                ResetSecondaryCounter(9);
            }
            break;
        }
