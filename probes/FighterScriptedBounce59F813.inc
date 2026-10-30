// F813: actual original 005214B0 action 0x59 (0052327A..005233DD), 356B /95 x86.
// Actor-specific genuine signed stage 3 and auxiliary action 3.
// Native game source interior; NOT an independently callable exact function.
        case 0x59: {
            if (S16(0x62)==3) {
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
                SetAuxActionAt40FB40(3);
            else if (S16(0x62)==3 && S16(0x64)==0) {
                POS=static_cast<float>(static_cast<int>(S16(0xF00)))*g_F747_BounceXAt006590BC;
                POS54=static_cast<float>(-static_cast<int>(S16(0xF02)))*g_F747_BounceYAt00658044;
                POS5C=0.7f;
                SetMotionStateAt40FBB0(0,95.0f,0);
            }
            break;
        }
