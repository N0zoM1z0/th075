// F701: restore entire original fighter 00543210 action0x302 native logic.
// Physical original 0055101E..005513C5: 935 B /261 instructions.
// Genuine four independent tier-specific projectile loops, not stubs.
// Nonexact boss-context source only; do not award whole-function credit.
        case 0x302: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                S16(0xF04)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(11);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==2 && S16(0x64)==0) {
                POS54=13.5f;
                POS=static_cast<float>(RandomBoundaryAt455580(0,8)-4);
                POS5C=0.25f;
            }
            if (S16(0x62)==9 && S16(0x64)==0) {
                PrepareActionAt453D40(18);
                S16(0x516)=120;
                S16(0xF04)=static_cast<short>(RandomBoundaryAt455580(0,359));
                if (g_CloudOpponentAt006714D0==0) {
                    for (int i=0; i<6; ++i) {
                        F32(0x314)=static_cast<float>(i*60+S16(0xF04));
                        SpawnFloatXYAt453A70(0x393,
                            F32(0x44)+g_ThresholdAt0065782C,
                            (*(&POS48))+g_F701_VolleyYAt00658268,
                            *reinterpret_cast<signed char*>(RAW+0x66),1);
                    }
                }
                if (g_CloudOpponentAt006714D0==1) {
                    for (int i=0; i<6; ++i) {
                        F32(0x314)=static_cast<float>(i*60+S16(0xF04));
                        SpawnFloatXYAt453A70(0x393,
                            F32(0x44)+g_ThresholdAt0065782C,
                            (*(&POS48))+g_F701_VolleyYAt00658268,
                            *reinterpret_cast<signed char*>(RAW+0x66),1);
                    }
                }
                if (g_CloudOpponentAt006714D0==2) {
                    for (int i=0; i<8; ++i) {
                        F32(0x314)=static_cast<float>(i*45+S16(0xF04));
                        SpawnFloatXYAt453A70(0x393,
                            F32(0x44)+g_ThresholdAt0065782C,
                            (*(&POS48))+g_F701_VolleyYAt00658268,
                            *reinterpret_cast<signed char*>(RAW+0x66),1);
                    }
                }
                if (g_CloudOpponentAt006714D0==3) {
                    for (int i=0; i<8; ++i) {
                        F32(0x314)=static_cast<float>(i*45+S16(0xF04));
                        SpawnFloatXYAt453A70(0x393,
                            F32(0x44)+g_ThresholdAt0065782C,
                            (*(&POS48))+g_F701_VolleyYAt00658268,
                            *reinterpret_cast<signed char*>(RAW+0x66),1);
                    }
                }
            }
            if (S16(0x62)==11 && S16(0x64)==0)
                SetAuxActionAt40FB40(9);
            break;
        }
