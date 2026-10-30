// F721: original complete native action 2E5 (0054F241..0054F55F):
// 798 original CODE B /223 x86. Genuine seven-argument projectile,
// original random direction/facing and stage-count based shots.
// Native original whole giant remains NONEXACT; no individual case credit.
        case 0x2E5: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                SpawnSevenAt453B50(0x38E,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=static_cast<short>(RandomBoundaryAt455580(60,80)
                   -static_cast<int>(g_CloudOpponentAt006714D0)*20);
            }
            if (S16(0x62)==3 && S16(0x64)==0)
                PrepareActionAt453D40(9);
            if (S16(0x62)==7 && S16(0x64)==0) {
                if (*reinterpret_cast<float*>(OWNER+0x48)==g_ThresholdAt0065782C)
                    S16(0xF00)=0;
                else
                    S16(0xF00)=20;
                if (RandomBoundaryAt455580(0,100)<20) {
                    if (RandomBoundaryAt455580(0,100)<50)
                        S16(0xF00)=0;
                    else
                        S16(0xF00)=20;
                }
                F32(0x314)=static_cast<float>(S16(0xF00));
                SpawnFloatXYAt453A70(0x386,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==10 && S16(0x64)==0
                && S16(0xF02)<(3-static_cast<int>(g_CloudOpponentAt006714D0))*2) {
                ++S16(0xF02);
                SetAuxActionAt40FB40(9);
            }
            if (S16(0x62)==12 && S16(0x64)==0) {
                F32(0x314)=static_cast<float>(S16(0xF00));
                if (S16(0xF00)==0)
                    SpawnFloatXYAt453A70(0x384,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                        (*(&POS48))+g_BarrageY1At006591EC,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                if (S16(0xF00)==20)
                    SpawnFloatXYAt453A70(0x388,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                        (*(&POS48))+g_BarrageY1At006591EC,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(10);
            }
            break;
        }
