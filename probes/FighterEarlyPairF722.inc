// F722: complete physical fighter action 0x2C0 and 0x2C1 in original giant.
// 2C0 original 0054D64D..0054D93E = 753 B/218 real x86.
// 2C1 original 0054D93E..0054DC0E = 720 B/214 real x86.
// 2C0 native IMUL +46/FSUBR is algebraically reproduced with -46/FADD
// to align the native FILD-before-X x87 order. Actual opcode/constant differ.
// Entire 00543210 original function still NONEXACT, no case credit.
        case 0x2C0: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=99;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<25 && POS48>g_ThresholdAt0065782C && S16(0x62)>15) {
                POS=POS-g_F718_FallingDragAt00659090;
                POS54=POS54-POS5C;
                if (POS<g_F718_BounceMinAt00657CF8)
                    POS=3.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(25);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==1 && S16(0x64)==0) {
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                SpawnAt453C80(0x73,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*-46)+F32(0x44),
                    (*(&POS48))+g_F722_BurstYAt0065826C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==7 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(11);
                POS54=9.0f;
                POS=20.0f;
                StartAnimationAt46D000(500);
                POS5C=0.8f;
            }
            if (S16(0x62)>6 && S16(0x62)<15) {
                SpawnFloatXYAt453A70(0x329,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==15 && S16(0x64)==0 && S16(0xF00)<3) {
                SetAuxActionAt40FB40(11);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==25 && S16(0x64)==0)
                SetAuxActionAt40FB40(23);
            break;
        }
        case 0x2C1: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                SpawnMixedAt453C80(0x74,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
            }
            if (S16(0x62)>3 && S16(0x62)<11) {
                POS54=POS54-g_F722_LowYAt00659A10;
                if (POS54<g_ThresholdAt0065782C)
                    POS54=0.0f;
            }
            if (S16(0x62)>10 && S16(0x62)<14) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(14);
                    break;
                }
            }
            if (S16(0x62)==5 && S16(0x64)==0)
                InitTrajectoryAt453E60(5.0f);
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=15.0f;
                POS5C=0.85f;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x32A,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    10.0f,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnDirectedAt453A70(0x340,I32(0x44),0,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(12);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<12) {
                SetAuxActionAt40FB40(5);
                ++S16(0xF00);
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<14) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            if (S16(0x62)==14 && S16(0x64)==0)
                SetAuxActionAt40FB40(12);
            break;
        }
