// F669: 0x255/0x256/0x257 authentic original fighter inner case C++.
// This is source-backed original stage movement/shots in the still NONEXACT
// full giant 00543210, not independently accepted whole game functions.
// The identity float lvalue expression preserves original FLD/FADD order.
case 0x255: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnMixedAt453C80(0x37,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<1) {
                ++S16(0xF00);
                SetAuxActionAt40FB40(6);
            }
            break;
        }
        case 0x256: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnMixedAt453C80(0x37,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }

            break;
        }
        case 0x257: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnMixedAt453C80(0x37,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<1) {
                ++S16(0xF00);
                SetAuxActionAt40FB40(6);
            }
            break;
        }
