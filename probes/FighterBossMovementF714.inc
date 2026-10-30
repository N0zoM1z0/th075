// F714: original physical native 00543210 action 2DC, complete 602B/169-x86.
// Real bounded handler: startup, floor motion, two native 0x333/0x387
// float projectiles, difficulty gate, terminal counter and state 4.
// Source-backed nonexact giant; never accept this as a whole game function.
        case 0x2DC: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0 && S16(0xF00)==0) {
                S16(0x80)=1;
                I32(0x7C)=0;
                S16(0xF00)=1;
                PrepareActionAt453D40(11);
                POS54=-10.0f;
                POS=30.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)<4 && POS48>g_ThresholdAt0065782C) {
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(4);
                    POS48=0.0f;
                    POS54=0.0f;
                    POS5C=0.0f;
                    break;
                }
            }
            if (S16(0x62)<4) {
                SpawnFloatXYAt453A70(0x333,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                if (g_CloudOpponentAt006714D0>1)
                    SpawnFloatXYAt453A70(0x387,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                        (*(&POS48))+g_F714_ShotYAt00657868,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)>3 && POS>g_ThresholdAt0065782C) {
                POS=POS-g_F714_DecelerationAt0065747C;
                if (POS<=g_ThresholdAt0065782C)
                    POS=0.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=static_cast<short>(RandomBoundaryAt455580(100,180)
                    -static_cast<int>(g_CloudOpponentAt006714D0)*30);
            }
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==4 && S16(0x64)==0)
                SetAuxActionAt40FB40(0);
            break;
        }
