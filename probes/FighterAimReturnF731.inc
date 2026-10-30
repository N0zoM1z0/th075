// F731: complete original fighter 1F8, native 0054B43A..0054B9F9,
// 1471 full CODE B /422 original x86. Full native stage, original
// 1FA transitions, contact/ground, 7D/7E reverse projectiles,
// real stage14 geometry through 00483300 /0040FB70 /0040FBB0,
// and stage15 338 projectile. Native 80.0f and NEG before FILD
// are confirmed by physical original PE, and *(&POS) restores
// direct C++ raw float argument use at native 00483300 call.
// Real target-Y member lvalue preserves native MOV/FLD owner order
// around the first 00483300 angle call. Two original memory FCOMP
// still emit extra FLD/FCOMPP; native deep EBP scratch not yet exact.
// Original entire fighter NONEXACT.
        case 0x1F8: {
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
                    SetMotionStateAt40FBB0(0,0.0f,0);
                    SetNativeActionAt40FAC0(0x1FA);
                    break;
                }
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS54=0.0f;
                    POS=POS*g_F728_PositiveDragAt006583FC;
                    SetAuxActionAt40FB40(16);
                    SetMotionStateAt40FBB0(0,0.0f,0);
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
                POS=30.0f;
                POS54=-30.0f;
                S16(0xF04)=static_cast<short>(
                    CalculateAngleAt483300(
                        *(&(*reinterpret_cast<float*>(OWNER+0x48)))-POS48,
                        ((*reinterpret_cast<float*>(OWNER+0x44))-F32(0x44))
                          *static_cast<float>(*reinterpret_cast<signed char*>(RAW+0x66)))
                      /g_StormAngleDenominatorAt00657828);
                if (S16(0xF04)>-15)
                    S16(0xF04)=-15;
                MotionAt40FB70(static_cast<float>(-static_cast<int>(S16(0xF04))),28.0f);
                SetMotionStateAt40FBB0(0,80.0f,0);
                F32(0x30)=-(CalculateAngleAt483300(POS54,*(&POS))
                             /g_StormAngleDenominatorAt00657828
                              +g_F731_AimOffsetAt00657CBC);
            }
            if (S16(0x62)==15 && S16(0x64)==0) {
                F32(0x314)=static_cast<float>(S16(0xF04));
                SpawnDirectedAt453A70(0x338,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==18 && S16(0x64)==0 && S16(0xF00)==0)
                SetAuxActionAt40FB40(19);
            if (S16(0x62)==11 && S16(0x64)==0)
                SetAuxActionAt40FB40(9);
            break;
        }
