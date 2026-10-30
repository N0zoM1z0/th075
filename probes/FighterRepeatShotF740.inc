// F740: two complete original repeated 0x330 volleys, part of the ONE
// 00543210 giant. Original 196 0054991A..00549ACE, 197
// 00549ACE..00549C82: each 436 native CODE bytes/118 x86.
// Real game-stage reset, motion, physical globals, and 6-shot gate.
// Original complete fighter CODE remains NONEXACT; no fake locals.
        case 0x196: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==6 && S16(0x64)==0) {
                PrepareActionAt453D40(2);
                F32(0x314)=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*60)+F32(0x44),
                    (*(&POS48))+g_F740_ShotY0At00659A1C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(100);
            }
            if (S16(0x62)==7 && S16(0x64)==0 && static_cast<unsigned int>(I32(0x4E8))>0
                    && S16(0xF00)<6 && S16(0x3B0)>0) {
                PrepareActionAt453D40(2);
                F32(0x314)=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*60)+F32(0x44),
                    (*(&POS48))+g_F740_ShotY0At00659A1C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(10);
                SetAuxActionAt40FB40(6);
                ++S16(0xF00);
            }
            break;
        }
        case 0x197: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==6 && S16(0x64)==0) {
                PrepareActionAt453D40(2);
                F32(0x314)=30.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*68)+F32(0x44),
                    (*(&POS48))+g_F740_ShotY1At0065928C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(100);
            }
            if (S16(0x62)==7 && S16(0x64)==0 && static_cast<unsigned int>(I32(0x4E8))>0
                    && S16(0xF00)<6 && S16(0x3B0)>0) {
                PrepareActionAt453D40(2);
                F32(0x314)=20.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*68)+F32(0x44),
                    (*(&POS48))+g_F740_ShotY1At0065928C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(10);
                SetAuxActionAt40FB40(6);
                ++S16(0xF00);
            }
            break;
        }
        case 0x198: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(1);
                F32(0x314)=60.0f;
                StartAnimationAt46D000(250);
                SpawnFloatXYAt453A70(0x347,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*28)+F32(0x44),
                    (*(&POS48))+g_F740_ShotY2At00659A18,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(2);
            break;
        }
