// F673: original fighter 00543210 native complete physical case 0x2BC.
// Normal pinned VC7.1 C++ source within a regenerated complete parent;
// no independent whole-function CODE credit, no artificial locals.
// Source method types remain provisional native ABI probes.
        case 0x2BC: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                ResetAt453E20();
                field36C=(field36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(0x17);
                SpawnMixedAt453C80(0x73,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<11) {
                velocityY=velocityY-g_FallDecelerationAt00659888;
                if (velocityY<g_ThresholdAt0065782C) velocityY=0.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>10 && (reinterpret_cast<signed short&>(animationStage))<14) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0xE);
                    break;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) InitTrajectoryAt453E60(2.0f);
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=15.0f;
                field05C=0.85f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                SpawnDirectedAt453A70(0x326,reinterpret_cast<int&>(x),0,
                    facing,1);
                SpawnDirectedAt453A70(0x33B,reinterpret_cast<int&>(x),0,
                    facing,1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(8);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<7) {
                SetAuxActionAt40FB40(5);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<9) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==14 && (reinterpret_cast<signed short&>(animationFrame))==0) SetAuxActionAt40FB40(12);
            break;
        }
