// F701: restore entire original fighter 00543210 action0x302 native logic.
// Physical original 0055101E..005513C5: 935 B /261 instructions.
// Genuine four independent tier-specific projectile loops, not stubs.
// Nonexact boss-context source only; do not award whole-function credit.
        case 0x302: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                reinterpret_cast<signed short&>(fieldF04)=0;
                field07C=1;
                ResetAt453E20();
            }
            if (y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(11);
                    y=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=13.5f;
                velocityX=static_cast<float>(RandomBoundaryAt455580(0,8)-4);
                field05C=0.25f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==9 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(18);
                reinterpret_cast<signed short&>(aiCardTimer)=120;
                reinterpret_cast<signed short&>(fieldF04)=static_cast<short>(RandomBoundaryAt455580(0,359));
                if (g_CloudOpponentAt006714D0==0) {
                    for (int i=0; i<6; ++i) {
                        field314=static_cast<float>(i*60+(reinterpret_cast<signed short&>(fieldF04)));
                        SpawnFloatXYAt453A70(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
                if (g_CloudOpponentAt006714D0==1) {
                    for (int i=0; i<6; ++i) {
                        field314=static_cast<float>(i*60+(reinterpret_cast<signed short&>(fieldF04)));
                        SpawnFloatXYAt453A70(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
                if (g_CloudOpponentAt006714D0==2) {
                    for (int i=0; i<8; ++i) {
                        field314=static_cast<float>(i*45+(reinterpret_cast<signed short&>(fieldF04)));
                        SpawnFloatXYAt453A70(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
                if (g_CloudOpponentAt006714D0==3) {
                    for (int i=0; i<8; ++i) {
                        field314=static_cast<float>(i*45+(reinterpret_cast<signed short&>(fieldF04)));
                        SpawnFloatXYAt453A70(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0)
                SetAuxActionAt40FB40(9);
            break;
        }
