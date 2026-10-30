// F732: complete native 1FA/1FB/1FE/1FF case interiors in one whole boss.
// Native original 0054B9F9..0054C18F: 1942 CODE B/562 x86/52 physical fields.
// Unlike historical F666 diagnostic source, 1FE/1FF real clamp must use
// strict POS < 00657CF8, emitting native TEST AH,5; JP (not >= AH1; JNE).
// New preceding authentic real-source stack local allocation naturally
// widens 1FA original ordinal 16/17 EBP scratch from old 3B to native 6B.
// The actual EBP slot and register phase still mismatch; whole 58KB NONEXACT.
// Original `FighterPrecedingStageGrammarF666.inc` retained as earlier evidence.
        case 0x1FA: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                POS=-5.0f;
                POS54=static_cast<float>(S16(0xF00)==1)*g_FloatMulAt00657874+g_FloatAddAt00657CBC;
                POS5C=-0.8f;
                I32(0x7C)=0;
                FLAG=0;
            }
            if (POS48>g_ThresholdAt0065782C && S16(0x62)<8) {
                POS54=POS54+POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetAuxActionAt40FB40(8);
                    POS48=0.0f;
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==8 && S16(0x64)==0) SetAuxActionAt40FB40(6);
            break;
        }
        case 0x1FB: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<8 && POS48>g_ThresholdAt0065782C && S16(0x62)>2)
                POS54=POS54-g_RisingGravityAt0065747C;
            if (S16(0x62)==10) {
                if (I32(0x7C)!=0 && I32(0x7C)!=3 && I32(0x7C)!=1) {
                    SetNativeActionAt40FAC0(0x1FA);
                    break;
                }
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS54=0.0f;
                    POS=POS*g_BounceScaleAt006583FC;
                    SetAuxActionAt40FB40(0xB);
                    POS48=0.0f;
                    break;
                }
            }
            if (S16(0x62)>10) {
                POS=POS-g_RisingDragAt006581E0;
                if (POS<g_ThresholdAt0065782C) POS=0.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==3 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                POS54=22.0f;
                POS5C=0.7f;
            }
            if (S16(0x62)==8 && S16(0x64)==0) ResetAt453E20();
            if (S16(0x62)==10 && S16(0x64)==0) {
                if (S16(0xF00)<1) {
                    SetAuxActionAt40FB40(8);
                    ++S16(0xF00);
                    break;
                }
                POS=20.0f;
                POS54=-20.0f;
            }
            if (S16(0x62)==11 && S16(0x64)==0) SetAuxActionAt40FB40(9);
            break;
        }
        case 0x1FE: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<18 && POS48>g_ThresholdAt0065782C && S16(0x62)>7) {
                POS=POS-g_ShotPositiveDragAt00659A10;
                POS54=POS54-POS5C;
                if (POS<g_SpeedClampAt00657CF8) POS=3.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(18);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==3 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(4);
                POS54=6.0f;
                POS=4.5f;
                POS5C=0.65f;
                SpawnDirectedAt453A70(0x33A,I32(0x44),I32(0x48),
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<0) {
                SetAuxActionAt40FB40(4);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==18 && S16(0x64)==0)
                SetAuxActionAt40FB40(16);
            break;
        }
        case 0x1FF: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<22 && POS48>g_ThresholdAt0065782C && S16(0x62)>12) {
                POS=POS-g_ShotPositiveDragAt00659A10;
                POS54=POS54-POS5C;
                if (POS<g_SpeedClampAt00657CF8) POS=3.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(22);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==3 && S16(0x64)==0) {
                PrepareActionAt453D40(4);
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                POS54=8.0f;
                POS=12.0f;
                POS5C=0.5f;
                SpawnDirectedAt453A70(0x33A,I32(0x44),I32(0x48),
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==12 && S16(0x64)==0 && S16(0xF00)<0) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==22 && S16(0x64)==0)
                SetAuxActionAt40FB40(20);
            break;
        }
