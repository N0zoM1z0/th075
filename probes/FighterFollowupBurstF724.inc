// F724: complete original fighter 00543210 action0x2C5 native
// 0054DDD2..0054E111: 831 CODE B/239 x86, not a new whole function.
// Original camera/motion reset, floor/drag/landing, native stage1
// 74 attack and trajectory, stage7 3C and 344 shots, stage15 loop.
// All exactness claims require original full giant; this is NONEXACT.
        case 0x2C5: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=99;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<25 && POS48>g_ThresholdAt0065782C && S16(0x62)>15) {
                POS=POS-g_F718_FallingDragAt00659090;
                POS54=POS54-POS5C;
                if (POS<g_F718_BounceMinAt00657CF8)
                    POS=3.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(25);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==1 && S16(0x64)==0) {
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                SpawnAt453C80(0x74,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*-46)+F32(0x44),
                    (*(&POS48))+g_F722_BurstYAt0065826C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
            }
            if (S16(0x62)==7 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x344,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*55)+F32(0x44),
                    (*(&POS48))+g_F724_ShotYAt00659488,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(15);
                POS54=10.5f;
                POS=25.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)>6 && S16(0x62)<15) {
                SpawnFloatXYAt453A70(0x32E,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==15 && S16(0x64)==0 && S16(0xF00)<5) {
                SetAuxActionAt40FB40(11);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==25 && S16(0x64)==0)
                SetAuxActionAt40FB40(23);
            break;
        }
