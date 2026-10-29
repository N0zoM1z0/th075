// F681: genuine original physical terminal 31B, 74 x86 /248 CODE B.
// In the selected whole parent with real 2F0/2F1 and 2F8 source this
// native case becomes context-strict (8 authentic typed REL32 fields).
// Actual saved-this role is source EBP-0xC, original PE EBP-0x44.
        case 0x31B: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==4 && S16(0x64)==0) {
                SubactionAt454A70(0);
                SubactionAt452B30();
                PrepareActionAt453D60(0x17);
                SpawnDirectedAt453A70(0x3E5,I32(0x44),I32(0x48),
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<8) {
                ++S16(0xF00);
                SetAuxActionAt40FB40(9);
            }
            break;
        }
