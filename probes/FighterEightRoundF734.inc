// F734: full native physical 00543210 0x190/0x191/0x192 8-shot cases.
// 190 00549364..00549478: 276 native CODE bytes/75 x86.
// 191 00549478..0054958C: 276 native CODE bytes/75 x86.
// 192 0054958C..0054967C: 240 native CODE bytes/68 x86.
// Actual stage/flags/8 volley projectiles and original member calls.
// These interiors are NOT separate original game functions.
        case 0x190: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (I32(0x4F0)==0)
                S16(0xF00)=1;
            if (S16(0x62)==5 && S16(0x64)==0) {
                PrepareActionAt453D40(0);
                F32(0x314)=0.0f;
                StartAnimationAt46D000(200);
                for (int shot=0; shot<8; ++shot) {
                    SpawnFloatXYAt453A70(0x324,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*70)+F32(0x44),
                        (*(&POS48))+g_F734_RoundY0At00659A30,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            break;
        }
        case 0x191: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (I32(0x4F0)==0)
                S16(0xF00)=1;
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(0);
                F32(0x314)=20.0f;
                StartAnimationAt46D000(200);
                for (int shot=0; shot<8; ++shot) {
                    SpawnFloatXYAt453A70(0x324,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*64)+F32(0x44),
                        (*(&POS48))+g_F734_RoundY1At00659A2C,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            break;
        }
        case 0x192: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(0);
                F32(0x314)=45.0f;
                StartAnimationAt46D000(200);
                for (int shot=0; shot<8; ++shot) {
                    SpawnFloatXYAt453A70(0x324,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*44)+F32(0x44),
                        (*(&POS48))+g_F734_RoundY2At00659A28,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(2);
            break;
        }
