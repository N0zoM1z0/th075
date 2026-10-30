// F744: genuinely used ordinary C++ for two COMPLETE original physical
// actions in enclosing 00543210 giant, NOT separate authored functions.
// 19A 00549D5C..00549FBB 607 native CODE B/166 x86;
// 19B 00549FBB..0054A21A 607 native CODE B/166 x86.
// Native stage, gravity, ground, two authentic 0x330 shots per action.
        case 0x19A: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                POS=POS*g_BounceScaleAt00657F74;
                POS54=(*(&POS54))*g_BounceScaleAt00657F74;
            }
            if (S16(0x62)>5) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    POS48=0.0f;
                    SetNativeActionAt40FAC0(10);
                    break;
                }
            }
            if (POS48+POS54<=g_ThresholdAt0065782C) {
                POS54=0.0f;
                POS=0.0f;
                POS48=0.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(9);
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(2);
                F32(0x314)=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*35)+F32(0x44),
                    (*(&POS48))+g_F737_RoundY0At00659A24,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(100);
            }
            if (S16(0x62)==5 && S16(0x64)==0
                    && static_cast<unsigned int>(I32(0x4E8))>0
                    && S16(0xF00)<6 && S16(0x3B0)>0) {
                PrepareActionAt453D40(2);
                F32(0x314)=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*35)+F32(0x44),
                    (*(&POS48))+g_F737_RoundY0At00659A24,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(20);
                SetAuxActionAt40FB40(4);
                ++S16(0xF00);
            }
            break;
        }
        case 0x19B: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                POS=POS*g_BounceScaleAt00657F74;
                POS54=(*(&POS54))*g_BounceScaleAt00657F74;
            }
            if (S16(0x62)>5) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    POS48=0.0f;
                    SetNativeActionAt40FAC0(10);
                    break;
                }
            }
            if (POS48+POS54<=g_ThresholdAt0065782C) {
                POS54=0.0f;
                POS=0.0f;
                POS48=0.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(9);
            if (S16(0x62)==4 && S16(0x64)==0) {
                PrepareActionAt453D40(2);
                F32(0x314)=-20.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*27)+F32(0x44),
                    (*(&POS48))+g_F737_RoundY1At00659A20,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(100);
            }
            if (S16(0x62)==5 && S16(0x64)==0
                    && static_cast<unsigned int>(I32(0x4E8))>0
                    && S16(0xF00)<6 && S16(0x3B0)>0) {
                PrepareActionAt453D40(2);
                F32(0x314)=-20.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*27)+F32(0x44),
                    (*(&POS48))+g_F737_RoundY1At00659A20,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(20);
                SetAuxActionAt40FB40(4);
                ++S16(0xF00);
            }
            break;
        }
