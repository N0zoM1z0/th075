// F711: real native 00543210 action2D0/2D1, each 416 B /120 x86.
// Different actual storm config, fall duration and random horizontal
// velocity; two native 7D/7E projectiles are retained in each case.
// Entire original fighter still NONEXACT; no independent function credit.
        case 0x2D0: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0) {
                POS=0.0f;
                S16(0xF00)=0;
            }
            if (POS48>g_ThresholdAt0065782C && S16(0x62)<7) {
                POS54=POS54-g_ApproachLowerAt00658290;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(7);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                break;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS=float(RandomBoundaryAt455580(0,15))+g_ApproachUpperAt006592A4;
                POS54=40.0f;
                POS5C=6.0f;
                SpawnAt453C80(0x7D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
                    (*(&POS48))+g_EightShotY2At00658268,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnMixedAt453C80(0x7E,I32(0x44),
                    (*(&POS48))+g_EightShotY2At00658268,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D60(31);
            }
            break;
        }
        case 0x2D1: {
            ConfigureStormAt454BC0(3,4,0xFF);
            if (S16(0x62)==0 && S16(0x64)==0) {
                POS=0.0f;
                S16(0xF00)=0;
            }
            if (POS48>g_ThresholdAt0065782C && S16(0x62)<6) {
                POS54=POS54-g_ApproachLowerAt00658290;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(6);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                break;
            }
            if (S16(0x62)==3 && S16(0x64)==0) {
                POS=g_F711_ReverseRandomAt00659A0C-float(RandomBoundaryAt455580(0,15));
                POS54=40.0f;
                POS5C=6.0f;
                SpawnAt453C80(0x7D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
                    (*(&POS48))+g_EightShotY2At00658268,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnMixedAt453C80(0x7E,I32(0x44),
                    (*(&POS48))+g_EightShotY2At00658268,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D60(31);
            }
            break;
        }
