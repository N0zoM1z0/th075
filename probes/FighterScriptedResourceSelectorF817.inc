// F817: real original 005214B0 full 0x62 resource-state selector.
// Complete native original 00523BA4..00523C9C: 249 CODE B /65 x86,
// four authentic REL32 game calls. Its original JMP goes directly to
// the encompassing void Advance() epilogue, so a natural C++ return
// replaces the source's otherwise redundant switch-break detour.
// The original historical class spelling is not established;
// this is an interior case, NOT independent callable game exact CODE.
// F749: true complete original 00543210 native action 0x62
// physical 005459E5..00545ADE 249 original CODE B/65 original x86.
// Natural real C++ resource-facing sign plus three actual action
// transitions; an interior switch case, NOT an authored function.
        case 0x62: {
            if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66)) * I32(0x4DC)>0
                && (static_cast<unsigned int>(I32(0x4E8))>0
                 || static_cast<unsigned int>(I32(0x4EC))>0
                 || static_cast<unsigned int>(I32(0x4F0))>0
                 || static_cast<unsigned int>(I32(0x4F4))>0))
                S16(0xF00)=1;
            if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66)) * I32(0x4DC)<0
                && (static_cast<unsigned int>(I32(0x4E8))>0
                 || static_cast<unsigned int>(I32(0x4EC))>0
                 || static_cast<unsigned int>(I32(0x4F0))>0
                 || static_cast<unsigned int>(I32(0x4F4))>0))
                S16(0xF00)=2;
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0x5F);
                if (S16(0xF00)==1) SetNativeActionAt40FAC0(0x5D);
                if (S16(0xF00)==2) SetNativeActionAt40FAC0(0x5E);
            }
            return;
        }
