// F715: original entire physical 00543210 action0x2DB,
// real 0054E451..0054E851: 1024 native CODE B /290 real x86.
// Complete original state, ground/contact and wall predicates, owner
// distance, signed-direction random choice, 7D/7E shots and 2DF/2DC
// transitions. Source is NONEXACT until entire original boss matches.
        case 0x2DB: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<10 && POS48>g_ThresholdAt0065782C && S16(0x62)>2) {
                POS=-30.0f;
                POS54=POS54-g_JumpGroundCorrectionAt00658058;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetNativeActionAt40FAC0(10);
                    POS48=0.0f;
                    break;
                }
            }
            if (S16(0x62)>9 && S16(0x62)<13 && !ContactAt454EE0()) {
                if (*reinterpret_cast<signed char*>(RAW+0x66)==1)
                    F32(0x44)=F32(0x2D8)+g_F699_SideOffsetAt00657874;
                if (*reinterpret_cast<signed char*>(RAW+0x66)==-1)
                    F32(0x44)=F32(0x2DC)-g_F699_SideOffsetAt00657874;
            }
            if (S16(0x62)>7 && S16(0x62)<10 && POS48>g_ThresholdAt0065782C
                && ContactAt454EE0()) {
                if ((F32(0x44)<=g_F699_SideEdgeAt00657884
                     && *reinterpret_cast<signed char*>(RAW+0x66)==1)
                    || (F32(0x44)>g_F699_SideEdgeAt00657884
                        && *reinterpret_cast<signed char*>(RAW+0x66)==-1)
                    || ((F32(0x2D8)+g_F699_SideOffsetAt00657874)>=F32(0x44)
                        && *reinterpret_cast<signed char*>(RAW+0x66)==1)
                    || ((F32(0x2DC)-g_F699_SideOffsetAt00657874)<=F32(0x44)
                        && *reinterpret_cast<signed char*>(RAW+0x66)==-1)) {
                    SetAuxActionAt40FB40(10);
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                if (S16(0xF00)<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++S16(0xF00);
                    SetAuxActionAt40FB40(12);
                    break;
                }
                S16(0xF00)=0;
                if (g_CloudOpponentAt006714D0==3) {
                    SetNativeActionAt40FAC0(0x2DF);
                    break;
                }
                if (POS48>g_F715_DecisionHeightAt006593D0)
                    SetNativeActionAt40FAC0(0x2DC);
                else
                    SetNativeActionAt40FAC0(0x2DC);
                break;
            }
            if (S16(0x62)==3 && S16(0x64)==0) {
                if (F699AbsAt00412D90(F32(0x44)-*reinterpret_cast<float*>(OWNER+0x44))
                    >=g_F699_DistanceAt0065787C) {
                    if (RandomBoundaryAt455580(0,100)<50)
                        *reinterpret_cast<signed char*>(RAW+0x66)=1;
                    else
                        *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                }
                PrepareActionAt453D40(5);
                SpawnAt453C80(0x7D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnMixedAt453C80(0x7E,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                POS=-20.0f;
                POS54=20.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)==10 && S16(0x64)==0)
                SetAuxActionAt40FB40(8);
            break;
        }
