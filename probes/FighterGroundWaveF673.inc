// F673: original fighter 00543210 native complete physical case 0x2BC.
// Normal pinned VC7.1 C++ source within a regenerated complete parent;
// no independent whole-function CODE credit, no artificial locals.
// Source method types remain provisional native ABI probes.
        case 0x2BC: {
            if ((animationStage)==0 && (animationFrame)==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                ClearMotionFields();
                field36C=(field36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PlaySharedSound(0x17);
                SpawnMixedAt453C80(0x73,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if ((animationStage)>3 && (animationStage)<11) {
                velocityY=velocityY-g_FallDecelerationAt00659888;
                if (velocityY<g_ThresholdAt0065782C) velocityY=0.0f;
            }
            if ((animationStage)>10 && (animationStage)<14) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0xE);
                    break;
                }
            }
            if ((animationStage)==5 && (animationFrame)==0) InitTrajectoryAt453E60(2.0f);
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityY=15.0f;
                field05C=0.85f;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnDirectedAt453A70(0x326,reinterpret_cast<int&>(x),0,
                    facing,1);
                SpawnDirectedAt453A70(0x33B,reinterpret_cast<int&>(x),0,
                    facing,1);
                UpdateGaugeTimer(500);
                PlaySound(8);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<7) {
                SetAuxActionAt40FB40(5);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((animationStage)==11 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<9) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((animationStage)==14 && (animationFrame)==0) SetAuxActionAt40FB40(12);
            break;
        }
