// F743: four real complete native physical actions from ONE original
// 00543210 fighter switch (all still NONEXACT as a 58KB parent).
// Original 19C 0054A21A..0054A2F4 218 B/62 x86;
// 19E 0054A2F4..0054A462 366 B/104 x86;
// 1A0 0054A462..0054A597 309 B/84 x86;
// 1A1 0054A597..0054A6CC 309 B/84 x86.
// Distinct stage, floor/velocity and actual 0x335 shots are NOT stubs.
        case 0x19C: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0) {
                PrepareActionAt453D40(3);
                F32(0x314)=0.0f;
                SpawnFloatXYAt453A70(0x335,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_F743_Y19CAt00659A14,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(200);
            }
            break;
        }
        case 0x19E: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
                S16(0xF00)=0;
            }
            if (POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    POS48=0.0f;
                    SetNativeActionAt40FAC0(10);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetAuxActionAt40FB40(10);
            if (S16(0x62)==2 && S16(0x64)==0) {
                POS=-6.0f;
                POS54=17.5f;
                POS5C=0.8f;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                PrepareActionAt453D40(3);
                F32(0x314)=-20.0f;
                SpawnFloatXYAt453A70(0x335,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*27)+F32(0x44),
                    (*(&POS48))+g_F737_RoundY1At00659A20,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(200);
            }
            break;
        }
        case 0x1A0: {
            if (S16(0x62)==0 && S16(0x64)==0)
                I32(0x7C)=1;
            POS54=POS54-POS5C;
            if (POS48+POS54<=g_ThresholdAt0065782C) {
                POS54=0.0f;
                POS=0.0f;
                POS48=0.0f;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(3);
                POS=-8.0f;
                POS54=10.0f;
                POS5C=0.65f;
                F32(0x314)=0.0f;
                StartAnimationAt46D000(200);
                SpawnFloatXYAt453A70(0x335,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*45)+F32(0x44),
                    (*(&POS48))+g_F743_Y1A0At00659288,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x1A1: {
            if (S16(0x62)==0 && S16(0x64)==0)
                I32(0x7C)=1;
            POS54=POS54-POS5C;
            if (POS48+POS54<=g_ThresholdAt0065782C) {
                POS54=0.0f;
                POS=0.0f;
                POS48=0.0f;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(3);
                POS=-8.0f;
                POS54=10.0f;
                POS5C=0.65f;
                F32(0x314)=-20.0f;
                StartAnimationAt46D000(200);
                SpawnFloatXYAt453A70(0x335,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*27)+F32(0x44),
                    (*(&POS48))+g_F737_RoundY1At00659A20,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(9);
            break;
        }
