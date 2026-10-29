// F676: full original giant 00543210 native case 2F0/2F1 C++ grammar.
// Original 342/274 x86, 1,169/977 CODE B and all 42/23 typed fields;
// these remain NONSTRICT because real original GPR phases do not agree.
// Historic source class and native float/raw argument ABIs are provisional.
        case 0x2F0: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                S16(0xF04)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)>3 && S16(0x62)<11) {
                POS54=POS54-g_CloudGravityAt0065785C;
                if (POS54<g_ThresholdAt0065782C) POS54=0.0f;
            }
            if (S16(0x62)>10 && S16(0x62)<14) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0xE);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=RandomBoundaryAt455580(60,100)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=13.5f;
                POS5C=0.15f;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnDirectedAt453A70(0x38C,I32(0x44),0,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnDirectedAt453A70(0x38F,I32(0x44),0,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(16);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<6) {
                SetAuxActionAt40FB40(5);
                ++S16(0xF00);
                if (S16(0xF00)==6-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&F32(0x44)))+g_ContactProjectionAt00657888,
                        0x41F00000,*reinterpret_cast<signed char*>(RAW+0x66),0);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&F32(0x44)))-g_ContactProjectionAt00657888,
                        0x41F00000,*reinterpret_cast<signed char*>(RAW+0x66),0);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&F32(0x44)))+g_BurstXAt00659238,
                        0,*reinterpret_cast<signed char*>(RAW+0x66),1);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&F32(0x44)))-g_BurstXAt00659238,
                        0,*reinterpret_cast<signed char*>(RAW+0x66),1);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&F32(0x44)))+g_BurstXAt00658400,
                        0xC1F00000,*reinterpret_cast<signed char*>(RAW+0x66),1);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&F32(0x44)))-g_BurstXAt00658400,
                        0xC1F00000,*reinterpret_cast<signed char*>(RAW+0x66),1);
                    if (static_cast<int>(g_CloudOpponentAt006714D0)>1) {
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&F32(0x44)))+g_BurstXAt00659420,
                            0x42480000,*reinterpret_cast<signed char*>(RAW+0x66),0);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&F32(0x44)))-g_BurstXAt00659420,
                            0x42480000,*reinterpret_cast<signed char*>(RAW+0x66),0);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&F32(0x44)))+g_BurstXAt00658370,
                            0,*reinterpret_cast<signed char*>(RAW+0x66),1);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&F32(0x44)))-g_BurstXAt00658370,
                            0,*reinterpret_cast<signed char*>(RAW+0x66),1);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&F32(0x44)))+g_BurstXAt006590A8,
                            0xC2480000,*reinterpret_cast<signed char*>(RAW+0x66),1);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&F32(0x44)))-g_BurstXAt006590A8,
                            0xC2480000,*reinterpret_cast<signed char*>(RAW+0x66),1);
                    }
                    InitTrajectoryAt453E60(10.0f);
                    PrepareActionAt453D40(20);
                }
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<5) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            break;
        }
        case 0x2F1: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                S16(0xF04)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)>3 && S16(0x62)<11) {
                POS54=POS54-g_CloudGravityAt0065785C;
                if (POS54<g_ThresholdAt0065782C) POS54=0.0f;
            }
            if (S16(0x62)>4 && S16(0x62)<8 && S16(0xF00)<3) {
                ++S16(0xF02);
                if (S16(0xF02)>4) {
                    SpawnMixedAt453C80(0x40,I32(0x44),
                       (*(&POS48))+g_CloudShotYAt006591E4,1,1);
                    S16(0xF02)=0;
                }
            }
            if (S16(0x62)>4 && S16(0x62)<8 && S16(0xF00)>3) {
                ++S16(0xF02);
                if (S16(0xF02)>2 &&
                    S16(0xF04)<static_cast<int>(g_CloudOpponentAt006714D0)*5+15) {
                    S16(0xF02)=0;
                    ++S16(0xF04);
                    if (RandomBoundaryAt455580(0,100)>50)
                        SpawnWithFloatAt453A70(0x390,I32(0x44),
                            (*(&POS48))+g_CloudShotYAt006591E4,1,1);
                    else
                        SpawnWithFloatAt453A70(0x390,I32(0x44),
                            (*(&POS48))+g_CloudShotYAt006591E4,-1,1);
                }
            }
            if (S16(0x62)>10 && S16(0x62)<14) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0xE);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=RandomBoundaryAt455580(60,120)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=16.5f;
                POS5C=0.15f;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnWithFloatAt453A70(0x38B,I32(0x44),
                    (*(&POS48))+g_CloudShotYAt006591E4,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(0x15);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<10) {
                SetAuxActionAt40FB40(5);
                ++S16(0xF00);
                if (S16(0xF00)==4) PrepareActionAt453D40(0x13);
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<5) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            break;
        }
