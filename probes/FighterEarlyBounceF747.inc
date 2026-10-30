// F747: true complete original 059/05D/05E normal C++ action interiors
// in ONE 58KB fighter 00543210 giant parent. No independent CODE credit.
// Native original 059 00545109..0054526D 356 B /95 x86;
// 05D 0054526D..005453BE 337 B/101 x86;
// 05E 005453BE..0054550F 337 B/101 x86.
        case 0x59: {
            if (S16(0x62)>1) {
                F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;
                POS54=POS54-POS5C;
                if (POS54+POS48<=g_ThresholdAt0065782C) {
                    S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
                    S16(0xF02)=static_cast<short>((*(&POS54))*g_ContactProjectionAt00657888);
                    ResetAt453E20();
                    POS48=0.0f;
                    SetNativeActionAt40FAC0(0x61);
                    F32(0x30)=0.0f;
                    InitTrajectoryAt453E60(2.0f);
                    ResetMotionAt40FC50();
                    PrepareActionAt453D60(0x16);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetAuxActionAt40FB40(2);
            else if (S16(0x62)==2 && S16(0x64)==0) {
                POS=static_cast<float>(static_cast<int>(S16(0xF00)))*g_F747_BounceXAt006590BC;
                POS54=static_cast<float>(-static_cast<int>(S16(0xF02)))*g_F747_BounceYAt00658044;
                POS5C=0.7f;
                SetMotionStateAt40FBB0(0,95.0f,0);
            }
            break;
        }
        case 0x5D: {
            if (S16(0x62)<8 && POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(8);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                if (I32(0x4E0)>0)
                    SetNativeActionAt40FAC0(1);
            }
            if (S16(0x62)==S16(0x70)-1) {
                if (F32(0x44)>(*reinterpret_cast<float*>(OWNER+0x44)))
                    *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                if (F32(0x44)<(*reinterpret_cast<float*>(OWNER+0x44)))
                    *reinterpret_cast<signed char*>(RAW+0x66)=1;
            }
            if (S16(0x62)==3 && S16(0x64)==0) {
                POS54=8.0f;
                POS=15.5f;
                POS5C=0.75f;
            }
            if (S16(0x62)==8 && S16(0x64)==0)
                SetAuxActionAt40FB40(6);
            break;
        }
        case 0x5E: {
            if (S16(0x62)<8 && POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(8);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                if (I32(0x4E0)>0)
                    SetNativeActionAt40FAC0(1);
            }
            if (S16(0x62)==S16(0x70)-1) {
                if (F32(0x44)>(*reinterpret_cast<float*>(OWNER+0x44)))
                    *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                if (F32(0x44)<(*reinterpret_cast<float*>(OWNER+0x44)))
                    *reinterpret_cast<signed char*>(RAW+0x66)=1;
            }
            if (S16(0x62)==3 && S16(0x64)==0) {
                POS54=8.0f;
                POS=-15.5f;
                POS5C=0.75f;
            }
            if (S16(0x62)==8 && S16(0x64)==0)
                SetAuxActionAt40FB40(6);
            break;
        }
