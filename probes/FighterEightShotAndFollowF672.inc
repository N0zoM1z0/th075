// F672: original fighter 00543210 full native 259..25D C++ case grammar.
// These five complete original source bodies remain NONSTRICT from real
// EBP integer-to-float scratch slot differences. Do NOT count exact.
// 259 contains eight original 321/322 shots; 25A..25D each one shot.
// Original PE global 00658264 is shared by 259 and 25B.
        case 0x259: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0) {
                StartAnimationAt46D000(250);
                F32(0x314)=-10.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_EightShotY0At006591F8,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_EightShotY0At006591F8,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x314)=10.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_EightShotY1At00658264,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_EightShotY1At00658264,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x314)=-6.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*75)+F32(0x44),
                    (*(&POS48))+g_BarrageY3At0065908C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*75)+F32(0x44),
                    (*(&POS48))+g_BarrageY3At0065908C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x314)=6.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*75)+F32(0x44),
                    (*(&POS48))+g_EightShotY2At00658268,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*75)+F32(0x44),
                    (*(&POS48))+g_EightShotY2At00658268,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            break;
        }
        case 0x25A: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                POS=POS*g_BounceScaleAt00657F74;
                POS54=(*(&POS54))*g_BounceScaleAt00657F74;
                I32(0x7C)=1;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x32B,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*100)+F32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x25B: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                POS=POS*g_BounceScaleAt00657F74;
                POS54=(*(&POS54))*g_BounceScaleAt00657F74;
                I32(0x7C)=1;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x32D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*100)+F32(0x44),
                    (*(&POS48))+g_EightShotY1At00658264,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x25C: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x332,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*70)+F32(0x44),
                    (*(&POS48))+g_OneShotYAt0065928C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            break;
        }
        case 0x25D: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x333,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*70)+F32(0x44),
                    (*(&POS48))+g_OneShotYAt0065928C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            break;
        }
