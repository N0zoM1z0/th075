// F661: actual original fighter 00543210 native shot cases 0x18A/0x18B.
// Full parent ordinary VC7.1 C++ source grammar, still NONSTRICT.
// FILD scratch operands remain genuinely nonexact against original native
// EBP-0x88 and EBP-0x8C. Do NOT credit either as strict native interior.
        case 0x18A: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0x80)=1;
                I32(0x7C)=0;
                POS=15.0f;
                S16(0xF00)=0;
            }
            POS=POS-g_JumpGroundCorrectionAt00658058;
            if (POS<g_ThresholdAt0065782C) {
                POS=0.0f;
                FLAG=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x327,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*151)+F32(0x44),
                    F32(0x48)+g_YPlusAt0065929C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            break;
        }
        case 0x18B: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0x80)=1;
                I32(0x7C)=0;
                POS=10.0f;
                S16(0xF00)=0;
            }
            if (S16(0x62)>6) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
            if (S16(0x62)==7 && S16(0x64)==0 && S16(0xF00)<2) {
                ++S16(0xF00);
                SetAuxActionAt40FB40(6);
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (S16(0x62)==6 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x328,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*128)+F32(0x44),
                    F32(0x48)+g_YPlusAt00658400,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            break;
        }
