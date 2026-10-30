// F708: true original 00543210 case2BF/2C4 dual projectile sequences.
// Each original physical handler is 452 B /131 x86, with real setup,
// signed -20*direction+X source is equivalent to X-20*direction and
// restores the original FILD-before-float evaluation order; original
// FSUBR vs compiler FADD and signed IMUL immediate still differ.
// stage-12 shots and distinct animation ordering. Whole boss NONEXACT.
        case 0x2BF: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                PrepareActionAt453D40(9);
                SpawnAt453C80(0x73,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*-20)+F32(0x44),
                    (*(&POS48))+g_BurstXAt00659238,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnSevenAt453B50(0x334,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==12 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x328,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x33C,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(10);
            }
            break;
        }
        case 0x2C4: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                PrepareActionAt453D40(13);
                SpawnAt453C80(0x74,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*-20)+F32(0x44),
                    (*(&POS48))+g_BurstXAt00659238,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnSevenAt453B50(0x334,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==12 && S16(0x64)==0) {
                StartAnimationAt46D000(750);
                SpawnFloatXYAt453A70(0x32B,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x33D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(14);
            }
            break;
        }
