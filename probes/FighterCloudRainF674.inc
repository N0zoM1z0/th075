// F674: original 00543210 full native action 2EF, 224 x86/788 CODE B.
// Genuine VC7.1 normal C++ within still-NONEXACT giant full parent;
// source method names/signatures are provisional original ABI grammar.
// A REAL subsequent native terminal stage is needed to restore the
// physical original 5-byte shared-exit JMP, not source padding.
        case 0x2EF: {
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
            if (S16(0x62)>4 && S16(0x62)<8) {
                ++S16(0xF02);
                ++S16(0xF04);
                if (S16(0xF02)>100-static_cast<int>(g_CloudOpponentAt006714D0)*20) {
                    S16(0xF02)=0;
                    PrepareActionAt453D40(0x10);
                    SpawnWithFloatAt453A70(0x389,I32(0x44),
                        (*(&POS48))+g_CloudShotYAt006591E4,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                    SpawnWithFloatAt453A70(0x38A,I32(0x44),
                        (*(&POS48))+g_CloudShotYAt006591E4,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
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
                S16(0x516)=RandomBoundaryAt455580(60,100)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=16.5f;
                POS5C=0.15f;
                PrepareActionAt453D40(0x15);
            }
            if (S16(0x62)==5 && S16(0x64)==0)
                SpawnWithFloatAt453A70(0x38B,I32(0x44),
                    (*(&POS48))+g_CloudShotYAt006591E4,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<25) {
                SetAuxActionAt40FB40(5);
                ++S16(0xF00);
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<25) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            break;
        }
