// F657: original fighter 00543210 physical stage 0x186..0x189 source grammar.
// Action 0x186 is deliberately still NONSTRICT (two original EBP−0x84
// temporary slots compile at EBP−0x20). Do not claim whole 186 exact.
// Three following full original native 187/188/189 cases are strictly
// compared against genuine original PE/typed COFF in the full parent.
        case 0x186: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                if (FLAG==0) ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                POS=10.0f;
            }
            if (S16(0x62)>0) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0) {
                InitTrajectoryAt453E60(2.0f);
                SpawnFloatXYAt453A70(0x325,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*170)+F32(0x44),
                    F32(0x48)-g_ApproachLowerAt00658290,
                    *reinterpret_cast<signed char*>(RAW+0x66),0);
            }
            break;
        }
        case 0x187: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                if (FLAG==0) ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                POS=10.0f;
            }
            if (S16(0x62)>0) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            break;
        }
        case 0x188: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                if (FLAG==0) ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                POS=15.0f;
            }
            if (S16(0x62)>0) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(2);
            break;
        }
        case 0x189: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                FLAG=0;
                S16(0x80)=1;
                I32(0x7C)=0;
                POS5C=0.0f;
                POS54=0.0f;
                POS=15.0f;
            }
            if (POS>g_ThresholdAt0065782C) POS=POS-g_SlowPositiveDragAt006578C0;
            if (POS48>g_ThresholdAt0065782C && S16(0x62)>6 && S16(0x62)<9) {
                POS54=POS54-POS5C;
                if (POS54+POS48<=g_ThresholdAt0065782C) {
                    POS=0.0f;
                    POS54=0.0f;
                    POS5C=0.0f;
                    POS48=0.0f;
                    S16(0x64)=0;
                    SetAuxActionAt40FB40(9);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==7 && S16(0x64)==0) {
                POS54=9.0f;
                POS5C=0.9f;
            }
            if (S16(0x62)==9 && POS48>g_ThresholdAt0065782C)
                SetAuxActionAt40FB40(S16(0x62)-2);
            break;
        }
