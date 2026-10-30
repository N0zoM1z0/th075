// F729: one of two complete original physical 00543210 return-bounce
// stages (1F6/1F7), instantiated twice with genuinely used values.
// 1F6: native 0054AB00..0054AF9D, 1181 CODE B /348 x86.
// 1F7: native 0054AF9D..0054B43A, 1181 CODE B /348 x86.
// First side-edge strict `<` recovers original TEST AH,5/JP. Third/
// fourth comparisons currently still naturally compile FLD/FCOMPP
// instead of native FCOMP [this+0x44]; NO byte-exact claim.
// All native stack/branch/physical fields must be proven in whole parent.
        case F729_CASE: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                U8(0x3AC)=0;
            }
            if (S16(0x62)<11 && POS48>g_ThresholdAt0065782C && S16(0x62)>2) {
                POS=-30.0f;
                POS54=POS54-g_ApproachAt00658058;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetAuxActionAt40FB40(15);
                    POS48=0.0f;
                    break;
                }
            }
            if (S16(0x62)>10 && S16(0x62)<14 && !ContactAt454EE0()) {
                if (*reinterpret_cast<signed char*>(RAW+0x66)==1)
                    F32(0x44)=F32(0x2D8)+g_F699_SideOffsetAt00657874;
                if (*reinterpret_cast<signed char*>(RAW+0x66)==-1)
                    F32(0x44)=F32(0x2DC)-g_F699_SideOffsetAt00657874;
            }
            if (S16(0x62)>8 && S16(0x62)<11
                && POS48>g_ThresholdAt0065782C && ContactAt454EE0()) {
                if ((F32(0x44)<g_F699_SideEdgeAt00657884
                        && *reinterpret_cast<signed char*>(RAW+0x66)==1)
                    || (F32(0x44)>g_F699_SideEdgeAt00657884
                        && *reinterpret_cast<signed char*>(RAW+0x66)==-1)
                    || ((F32(0x2D8)+g_F699_SideOffsetAt00657874)>=F32(0x44)
                        && *reinterpret_cast<signed char*>(RAW+0x66)==1)
                    || ((F32(0x2DC)-g_F699_SideOffsetAt00657874)<=F32(0x44)
                        && *reinterpret_cast<signed char*>(RAW+0x66)==-1)) {
                    SetAuxActionAt40FB40(11);
                    ResetAt453E20();
                    break;
                }
            }
            if (S16(0x62)==14 || S16(0x62)==15) {
                if (I32(0x7C)!=0 && I32(0x7C)!=3 && I32(0x7C)!=1) {
                    SetNativeActionAt40FAC0(0x1FA);
                    break;
                }
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS54=0.0f;
                    POS=POS*g_F728_PositiveDragAt006583FC;
                    SetAuxActionAt40FB40(16);
                    POS48=0.0f;
                    break;
                }
            }
            if (S16(0x62)>15) {
                POS=POS-g_NewDragAt006581E0;
                if (POS<g_ThresholdAt0065782C)
                    POS=0.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==3 && S16(0x64)==0) {
                PrepareActionAt453D40(5);
                SpawnAt453C80(0x7D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    -*reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnMixedAt453C80(0x7E,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    -*reinterpret_cast<signed char*>(RAW+0x66),1);
                POS=-20.0f;
                POS54=20.0f;
                if (POS48>g_ThresholdAt0065782C)
                    POS54=8.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)==14 && S16(0x64)==0) {
                PrepareActionAt453D40(6);
                POS=F729_STAGE14_X;
                POS54=F729_STAGE14_Y;
            }
            if (S16(0x62)==15 && S16(0x64)==0)
                SpawnDirectedAt453A70(F729_STAGE15_SHOT,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            if (S16(0x62)==18 && S16(0x64)==0 && S16(0xF00)==0)
                SetAuxActionAt40FB40(19);
            if (S16(0x62)==11 && S16(0x64)==0)
                SetAuxActionAt40FB40(9);
            break;
        }
