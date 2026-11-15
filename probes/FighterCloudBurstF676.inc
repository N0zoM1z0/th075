// F676: full original giant 00543210 native case 2F0/2F1 C++ grammar.
// Original 342/274 x86, 1,169/977 CODE B and all 42/23 typed fields;
// these remain NONSTRICT because real original GPR phases do not agree.
// Historic source class and native float/raw argument ABIs are provisional.
        case 0x2F0: {
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
                velocityY=13.5f;
                field05C=0.15f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                SpawnDirectedAt453A70(0x38C,reinterpret_cast<int&>(x),0,
                    facing,1);
                SpawnDirectedAt453A70(0x38F,reinterpret_cast<int&>(x),0,
                    facing,1);
                PrepareActionAt453D40(16);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<6) {
                SetAuxActionAt40FB40(5);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                if ((reinterpret_cast<signed short&>(scriptCounterF00))==6-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&x))+g_ContactProjectionAt00657888,
                        0x41F00000,facing,0);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&x))-g_ContactProjectionAt00657888,
                        0x41F00000,facing,0);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&x))+g_BurstXAt00659238,
                        0,facing,1);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&x))-g_BurstXAt00659238,
                        0,facing,1);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&x))+g_BurstXAt00658400,
                        0xC1F00000,facing,1);
                    SpawnFloatXRawYAt453A70(0x38D,
                        (*(&x))-g_BurstXAt00658400,
                        0xC1F00000,facing,1);
                    if (static_cast<int>(g_CloudOpponentAt006714D0)>1) {
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&x))+g_BurstXAt00659420,
                            0x42480000,facing,0);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&x))-g_BurstXAt00659420,
                            0x42480000,facing,0);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&x))+g_BurstXAt00658370,
                            0,facing,1);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&x))-g_BurstXAt00658370,
                            0,facing,1);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&x))+g_BurstXAt006590A8,
                            0xC2480000,facing,1);
                        SpawnFloatXRawYAt453A70(0x38D,
                            (*(&x))-g_BurstXAt006590A8,
                            0xC2480000,facing,1);
                    }
                    InitTrajectoryAt453E60(20.0f);
                    PrepareActionAt453D40(20);
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<5) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
        case 0x2F1: {
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
            if ((reinterpret_cast<signed short&>(animationStage))>4 && (reinterpret_cast<signed short&>(animationStage))<8 && (reinterpret_cast<signed short&>(scriptCounterF00))<3) {
                ++reinterpret_cast<signed short&>(scriptCounterF02);
                if ((reinterpret_cast<signed short&>(scriptCounterF02))>4) {
                    SpawnMixedAt453C80(0x40,reinterpret_cast<int&>(x),
                       (*(&y))+g_CloudShotYAt006591E4,1,1);
                    reinterpret_cast<signed short&>(scriptCounterF02)=0;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))>4 && (reinterpret_cast<signed short&>(animationStage))<8 && (reinterpret_cast<signed short&>(scriptCounterF00))>3) {
                ++reinterpret_cast<signed short&>(scriptCounterF02);
                if ((reinterpret_cast<signed short&>(scriptCounterF02))>2 &&
                    (reinterpret_cast<signed short&>(fieldF04))<static_cast<int>(g_CloudOpponentAt006714D0)*5+15) {
                    reinterpret_cast<signed short&>(scriptCounterF02)=0;
                    ++reinterpret_cast<signed short&>(fieldF04);
                    if (RandomBoundaryAt455580(0,100)>50)
                        SpawnWithFloatAt453A70(0x390,reinterpret_cast<int&>(x),
                            (*(&y))+g_CloudShotYAt006591E4,1,1);
                    else
                        SpawnWithFloatAt453A70(0x390,reinterpret_cast<int&>(x),
                            (*(&y))+g_CloudShotYAt006591E4,-1,1);
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
                reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(60,120)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=16.5f;
                field05C=0.15f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                SpawnWithFloatAt453A70(0x38B,reinterpret_cast<int&>(x),
                    (*(&y))+g_CloudShotYAt006591E4,
                    facing,1);
                PrepareActionAt453D40(0x15);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
                SetAuxActionAt40FB40(5);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                if ((reinterpret_cast<signed short&>(scriptCounterF00))==4) PrepareActionAt453D40(0x13);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<5) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
