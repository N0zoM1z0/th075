// F942: two genuine original 004AC040 resource/burst actions 0x60/0x61
// each 553 original CODE bytes /158 x86 /10 PE global or call fields.
// Original stage 2 < frame < 6, auxiliary action6 and initialization
// stage3 independently read from the SHA-pinned native game PE.
// This C++ is only an internal fragment of the still NONEXACT 82KB
// original fighter. Never credit it as a whole independent function.
// F748 genuine original 00543210 C++ resource-ten-volley actions.
// 060 native 0054559F..005457BC 541 B/154 original x86,
// 061 native 005457BC..005459E5 553 B/158 original x86.
// Source is full meaningful case semantics within ONE 58KB giant,
// not whole-function byte-exact CODE or a stand-alone function.
        case 0x60: {
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
            if (S16(0x62)==0 && S16(0x64)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
                if (S16(0xEFA)>25) {
                    S16(0xEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
                }
            }
            if (S16(0x62)>2 && S16(0x62)<6) {
                POS54=POS54-POS5C;
                if (POS54+POS48<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(6);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0x62);
                if (U8(0x3CF)==0)
                    SetNativeActionAt40FAC0(0x63);
            } else if (S16(0x62)==3 && S16(0x64)==0) {
                POS=static_cast<float>(static_cast<int>(S16(0xF00)))*g_F748_SpeedScaleAt006590B8;
                POS54=static_cast<float>(-static_cast<int>(S16(0xF02)))*g_F748_SpeedScaleAt006590B8;
                POS5C=2.0f;
            }
            break;
        }
        case 0x61: {
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
            if (S16(0x62)==0 && S16(0x64)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
                if (S16(0xEFA)>25) {
                    S16(0xEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
                }
            }
            if (S16(0x62)>2 && S16(0x62)<6) {
                POS54=POS54-POS5C;
                if (POS54+POS48<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(6);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0x62);
                if (U8(0x3CF)==0)
                    SetNativeActionAt40FAC0(0x63);
            } else if (S16(0x62)==3 && S16(0x64)==0) {
                POS=static_cast<float>(static_cast<int>(S16(0xF00)))*g_F748_SpeedScaleAt006590B8;
                POS54=static_cast<float>(-static_cast<int>(S16(0xF02)))*g_F748_SpeedScaleAt006590B8;
                POS5C=2.0f;
            }
            break;
        }
