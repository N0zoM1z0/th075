// F718: complete physical 00543210 action 2DD /2DE original native source.
// 2DD 0054EAAB..0054ED53: 680 B /189 native x86.
// 2DE 0054ED53..0054EFE7: 660 B /189 native x86.
// Native behavioral branches and typed PE calls retained; whole giant NONEXACT.
        case 0x2DD: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0 && S16(0xF00)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                PrepareActionAt453D40(11);
                POS54=10.0f;
                POS=30.0f;
                POS5C=0.45f;
                S16(0xF00)=1;
            }
            if (S16(0x62)<9 && POS48>g_ThresholdAt0065782C && S16(0x62)>3) {
                POS=POS-g_NewDragAt006581E0;
                POS54=POS54-POS5C;
                if (POS<g_StopThresholdAt00657480)
                    POS=2.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(9);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (S16(0x62)<4) {
                SpawnFloatXYAt453A70(0x329,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x387,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=static_cast<short>(RandomBoundaryAt455580(100,180)
                      -static_cast<int>(g_CloudOpponentAt006714D0)*30);
            }
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==4 && S16(0x64)==0 && S16(0xF00)<4) {
                SetAuxActionAt40FB40(0);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==9 && S16(0x64)==0)
                SetAuxActionAt40FB40(7);
            break;
        }
        case 0x2DE: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=99;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<25 && POS48>g_ThresholdAt0065782C && S16(0x62)>14) {
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
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=static_cast<short>(RandomBoundaryAt455580(100,180)
                      -static_cast<int>(g_CloudOpponentAt006714D0)*30);
            }
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==7 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(11);
                POS54=9.0f;
                POS=20.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)>6 && S16(0x62)<16) {
                SpawnFloatXYAt453A70(0x329,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==16 && S16(0x64)==0 && S16(0xF00)<3) {
                SetAuxActionAt40FB40(12);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==25 && S16(0x64)==0)
                SetAuxActionAt40FB40(23);
            break;
        }
