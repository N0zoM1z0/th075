// F813: actual original 005214B0 action 0x59 (0052327A..005233DD), 356B /95 x86.
// Actor-specific genuine signed stage 3 and auxiliary action 3.
// Native game source interior; NOT an independently callable exact function.
        case 0x59: {
            if ((animationStage)==3) {
                rotationZ=(rotationZ)+g_F728_RandomOffsetYAt00657858;
                velocityY=velocityY-field05C;
                if (velocityY+y<=g_ThresholdAt0065782C) {
                    reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
                    reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((*(&velocityY))*g_ContactProjectionAt00657888);
                    ClearMotionFields();
                    y=0.0f;
                    SetNativeActionAt40FAC0(0x61);
                    rotationZ=0.0f;
                    InitTrajectoryAt453E60(2.0f);
                    ResetMotionAt40FC50();
                    PrepareActionAt453D60(0x16);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(field070))
                SetAuxActionAt40FB40(3);
            else if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=static_cast<float>(static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF00)))*g_F747_BounceXAt006590BC;
                velocityY=static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF02)))*g_F747_BounceYAt00658044;
                field05C=0.7f;
                SetMotionStateAt40FBB0(0,95.0f,0);
            }
            break;
        }
