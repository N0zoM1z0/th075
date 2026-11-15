// F681: genuine original physical terminal 31B, 74 x86 /248 CODE B.
// In the selected whole parent with real 2F0/2F1 and 2F8 source this
// native case becomes context-strict (8 authentic typed REL32 fields).
// Actual saved-this role is source EBP-0xC, original PE EBP-0x44.
        case 0x31B: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                ResetAt453E20();
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                SubactionAt454A70(0);
                SubactionAt452B30();
                PrepareActionAt453D60(0x17);
                SpawnDirectedAt453A70(0x3E5,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                        facing,1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                SetAuxActionAt40FB40(9);
            }
            break;
        }
