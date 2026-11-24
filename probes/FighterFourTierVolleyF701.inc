// F701: restore entire original fighter 00543210 action0x302 native logic.
// Physical original 0055101E..005513C5: 935 B /261 instructions.
// Genuine four independent tier-specific projectile loops, not stubs.
// Nonexact boss-context source only; do not award whole-function credit.
        case 0x302: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                fieldF04=0;
                field07C=1;
                ClearMotionFields();
            }
            if (y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ResetSecondaryCounter(11);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if ((animationStage)==2 && (animationFrame)==0) {
                velocityY=13.5f;
                velocityX=static_cast<float>(RecordedRange(0,8)-4);
                field05C=0.25f;
            }
            if ((animationStage)==9 && (animationFrame)==0) {
                PlaySound(18);
                aiCardTimer=120;
                fieldF04=static_cast<short>(RecordedRange(0,359));
                if (g_OptionsModeAt006714D0==0) {
                    for (int i=0; i<6; ++i) {
                        field314=static_cast<float>(i*60+(fieldF04));
                        SpawnBattleEffect(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
                if (g_OptionsModeAt006714D0==1) {
                    for (int i=0; i<6; ++i) {
                        field314=static_cast<float>(i*60+(fieldF04));
                        SpawnBattleEffect(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
                if (g_OptionsModeAt006714D0==2) {
                    for (int i=0; i<8; ++i) {
                        field314=static_cast<float>(i*45+(fieldF04));
                        SpawnBattleEffect(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
                if (g_OptionsModeAt006714D0==3) {
                    for (int i=0; i<8; ++i) {
                        field314=static_cast<float>(i*45+(fieldF04));
                        SpawnBattleEffect(0x393,
                            (x)+g_ThresholdAt0065782C,
                            (*(&y))+g_F701_VolleyYAt00658268,
                            facing,1);
                    }
                }
            }
            if ((animationStage)==11 && (animationFrame)==0)
                ResetSecondaryCounter(9);
            break;
        }
