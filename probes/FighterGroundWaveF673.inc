// F673: original fighter 00543210 native complete physical case 0x2BC.
// Normal pinned VC7.1 C++ source within a regenerated complete parent;
// no independent whole-function CODE credit, no artificial locals.
// Source method types remain provisional native ABI probes.
        case 0x2BC: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(0x17);
                SpawnMixedAt453C80(0x73,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)>3 && S16(0x62)<11) {
                POS54=POS54-g_FallDecelerationAt00659888;
                if (POS54<g_ThresholdAt0065782C) POS54=0.0f;
            }
            if (S16(0x62)>10 && S16(0x62)<14) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0xE);
                    break;
                }
            }
            if (S16(0x62)==5 && S16(0x64)==0) InitTrajectoryAt453E60(2.0f);
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=15.0f;
                POS5C=0.85f;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnDirectedAt453A70(0x326,I32(0x44),0,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnDirectedAt453A70(0x33B,I32(0x44),0,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(8);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<7) {
                SetAuxActionAt40FB40(5);
                ++S16(0xF00);
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<9) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            if (S16(0x62)==14 && S16(0x64)==0) SetAuxActionAt40FB40(12);
            break;
        }
