// F674: original 00543210 full native action 2EF, 224 x86/788 CODE B.
// Genuine VC7.1 normal C++ within still-NONEXACT giant full parent;
// source method names/signatures are provisional original ABI grammar.
// A REAL subsequent native terminal stage is needed to restore the
// physical original 5-byte shared-exit JMP, not source padding.
        case 0x2EF: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                reinterpret_cast<signed short&>(fieldF04)=0;
                field07C=1;
                ResetAt453E20();
            }
            if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<11) {
                velocityY=velocityY-g_CloudGravityAt0065785C;
                if (velocityY<g_ThresholdAt0065782C) velocityY=0.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>4 && (reinterpret_cast<signed short&>(animationStage))<8) {
                ++reinterpret_cast<signed short&>(scriptCounterF02);
                ++reinterpret_cast<signed short&>(fieldF04);
                if ((reinterpret_cast<signed short&>(scriptCounterF02))>100-static_cast<int>(g_CloudOpponentAt006714D0)*20) {
                    reinterpret_cast<signed short&>(scriptCounterF02)=0;
                    PrepareActionAt453D40(0x10);
                    SpawnWithFloatAt453A70(0x389,reinterpret_cast<int&>(x),
                        (*(&y))+g_CloudShotYAt006591E4,
                        facing,1);
                    SpawnWithFloatAt453A70(0x38A,reinterpret_cast<int&>(x),
                        (*(&y))+g_CloudShotYAt006591E4,
                        facing,1);
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))>10 && (reinterpret_cast<signed short&>(animationStage))<14) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0xE);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(60,100)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=16.5f;
                field05C=0.15f;
                PrepareActionAt453D40(0x15);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0)
                SpawnWithFloatAt453A70(0x38B,reinterpret_cast<int&>(x),
                    (*(&y))+g_CloudShotYAt006591E4,
                    facing,1);
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<25) {
                SetAuxActionAt40FB40(5);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<25) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
