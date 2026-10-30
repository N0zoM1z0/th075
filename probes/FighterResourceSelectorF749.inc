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
            break;
        }
