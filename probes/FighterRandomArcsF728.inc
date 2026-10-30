// F728: two complete physical 00543210 original random-arc game actions.
// 1F4: 0054A6CC..0054A8E6, 538 native CODE B /149 x86.
// 1F5: 0054A8E6..0054AB00, 538 native CODE B /149 x86.
// Member Y is deliberately read via a genuine lvalue before the native
// 00657858 FADD: VC7.1 now owns the original DIR32 at x86 ordinal
// 36/55, not a source-only FLD of the global before member FADD.
// All four x87 intermediate stack owners remain NONEXACT in each case.
// Full real float shot/motion/ground/action source, whole giant NONEXACT.
        case 0x1F4: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                U8(0x3AC)=0;
            }
            if (RandomBoundaryAt455580(0,100)<40 && S16(0x62)>3 && S16(0x62)<8) {
                SpawnFloatXYAt453A70(0x330,
                    (F32(0x44)+g_F728_RandomOffsetXAt00657878)
                        -float(RandomBoundaryAt455580(0,60)),
                    ((*(&POS48))+g_F728_RandomOffsetYAt00657858)
                        +float(RandomBoundaryAt455580(0,140)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (POS>g_ThresholdAt0065782C) {
                POS=POS-g_F728_PositiveDragAt006583FC;
                if (POS<g_ThresholdAt0065782C)
                    POS=0.0f;
            }
            if (POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetAuxActionAt40FB40(12);
                    POS48=0.0f;
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(4);
                POS=8.0f;
                POS54=14.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)==18 && S16(0x64)==0)
                SetAuxActionAt40FB40(16);
            break;
        }
        case 0x1F5: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                U8(0x3AC)=0;
            }
            if (POS>g_ThresholdAt0065782C) {
                POS=POS-g_F728_PositiveDrag2At00658058;
                if (POS<g_ThresholdAt0065782C)
                    POS=0.0f;
            }
            if (RandomBoundaryAt455580(0,100)<40 && S16(0x62)>3 && S16(0x62)<8) {
                SpawnFloatXYAt453A70(0x330,
                    (F32(0x44)+g_F728_RandomOffsetXAt00657878)
                        -float(RandomBoundaryAt455580(0,60)),
                    ((*(&POS48))+g_F728_RandomOffsetYAt00657858)
                        +float(RandomBoundaryAt455580(0,140)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetAuxActionAt40FB40(12);
                    POS48=0.0f;
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(4);
                POS=18.0f;
                POS54=16.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)==12 && S16(0x64)==0)
                SetAuxActionAt40FB40(10);
            break;
        }
