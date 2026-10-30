// F737: two entire native grounded eight-shot actions in the true
// 00543210 giant. Original 194 = 0054967C..005497CB (335 B/92 x86),
// 195 = 005497CB..0054991A (335 B/92 x86). These are action bodies,
// NOT standalone original game functions or accepted exact CODE.
        case 0x194: {
            if (S16(0x62)==0 && S16(0x64)==0)
                I32(0x7C)=1;
            POS54=POS54-POS5C;
            if ((POS48+POS54)<=g_ThresholdAt0065782C) {
                POS54=0.0f;
                POS=0.0f;
                POS48=0.0f;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(0);
                POS=-4.0f;
                POS54=9.0f;
                POS5C=0.65f;
                F32(0x314)=0.0f;
                StartAnimationAt46D000(200);
                for (int shot=0;shot<8;++shot) {
                    SpawnFloatXYAt453A70(0x324,
                       float(*reinterpret_cast<signed char*>(RAW+0x66)*35)+F32(0x44),
                       (*(&POS48))+g_F737_RoundY0At00659A24,
                       *reinterpret_cast<signed char*>(RAW+0x66),1);
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x195: {
            if (S16(0x62)==0 && S16(0x64)==0)
                I32(0x7C)=1;
            POS54=POS54-POS5C;
            if ((POS48+POS54)<=g_ThresholdAt0065782C) {
                POS54=0.0f;
                POS=0.0f;
                POS48=0.0f;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(0);
                POS=-4.0f;
                POS54=9.0f;
                POS5C=0.65f;
                F32(0x314)=-30.0f;
                StartAnimationAt46D000(200);
                for (int shot=0;shot<8;++shot) {
                    SpawnFloatXYAt453A70(0x324,
                       float(*reinterpret_cast<signed char*>(RAW+0x66)*27)+F32(0x44),
                       (*(&POS48))+g_F737_RoundY1At00659A20,
                       *reinterpret_cast<signed char*>(RAW+0x66),1);
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(9);
            break;
        }
