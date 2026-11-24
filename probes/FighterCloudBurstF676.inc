// Remilia's cloud-burst actions 0x2F0 and 0x2F1 inside 0x00543210.
        case 0x2F0: {
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                fieldF04=0;
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)>3 && (animationStage)<11) {
                velocityY=velocityY-g_CloudGravityAt0065785C;
                if (velocityY<FloatConstants::Zero) velocityY=0.0f;
            } else if (animationStage >= 0 && animationStage < 4) {
                // The preparation stages keep their current vertical speed.
            }
            if ((animationStage)>10 && (animationStage)<14) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(0xE);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                aiCardTimer=RecordedRange(60,100)
                           -static_cast<int>(g_OptionsModeAt006714D0)*20;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityY=13.5f;
                field05C=0.15f;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x38C,x,0.0f,
                    facing,1);
                SpawnBattleEffect(0x38F,x,0.0f,
                    facing,1);
                PlaySound(16);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<6) {
                ResetSecondaryCounter(5);
                ++scriptCounterF00;
                if ((scriptCounterF00)==6-static_cast<int>(g_OptionsModeAt006714D0)) {
                    Fighter::SpawnBattleEffect(0x38D,
                        (*(&x))+g_ContactProjectionAt00657888,
                        30.0f,facing,0);
                    Fighter::SpawnBattleEffect(0x38D,
                        (*(&x))-g_ContactProjectionAt00657888,
                        30.0f,facing,0);
                    Fighter::SpawnBattleEffect(0x38D,
                        (*(&x))+g_BurstXAt00659238,
                        0.0f,facing,1);
                    Fighter::SpawnBattleEffect(0x38D,
                        (*(&x))-g_BurstXAt00659238,
                        0.0f,facing,1);
                    Fighter::SpawnBattleEffect(0x38D,
                        (*(&x))+g_BurstXAt00658400,
                        -30.0f,facing,1);
                    Fighter::SpawnBattleEffect(0x38D,
                        (*(&x))-g_BurstXAt00658400,
                        -30.0f,facing,1);
                    if (static_cast<int>(g_OptionsModeAt006714D0)>1) {
                        Fighter::SpawnBattleEffect(0x38D,
                            (*(&x))+g_BurstXAt00659420,
                            50.0f,facing,0);
                        Fighter::SpawnBattleEffect(0x38D,
                            (*(&x))-g_BurstXAt00659420,
                            50.0f,facing,0);
                        Fighter::SpawnBattleEffect(0x38D,
                            (*(&x))+g_BurstXAt00658370,
                            0.0f,facing,1);
                        Fighter::SpawnBattleEffect(0x38D,
                            (*(&x))-g_BurstXAt00658370,
                            0.0f,facing,1);
                        Fighter::SpawnBattleEffect(0x38D,
                            (*(&x))+g_BurstXAt006590A8,
                            -50.0f,facing,1);
                        Fighter::SpawnBattleEffect(0x38D,
                            (*(&x))-g_BurstXAt006590A8,
                            -50.0f,facing,1);
                    }
                    SetCameraShake(20.0f);
                    PlaySound(20);
                }
            }
            if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<5) {
                ResetSecondaryCounter(8);
                ++scriptCounterF00;
            }
            break;
        }
        case 0x2F1: {
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                fieldF04=0;
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)>3 && (animationStage)<11) {
                velocityY=velocityY-g_CloudGravityAt0065785C;
                if (velocityY<FloatConstants::Zero) velocityY=0.0f;
            }
            if ((animationStage)>4 && (animationStage)<8 && (scriptCounterF00)<3) {
                ++scriptCounterF02;
                if ((scriptCounterF02)>4) {
                    SpawnAuxEffect(0x40,x,
                       (*(&y))+g_CloudShotYAt006591E4,1,1);
                    scriptCounterF02=0;
                }
            }
            if ((animationStage)>4 && (animationStage)<8 && (scriptCounterF00)>3) {
                ++scriptCounterF02;
                if ((scriptCounterF02)>2 &&
                    (fieldF04)<static_cast<int>(g_OptionsModeAt006714D0)*5+15) {
                    scriptCounterF02=0;
                    ++fieldF04;
                    if (RecordedRange(0,100)>50)
                        SpawnBattleEffect(0x390,x,
                            (*(&y))+g_CloudShotYAt006591E4,1,1);
                    else
                        SpawnBattleEffect(0x390,x,
                            (*(&y))+g_CloudShotYAt006591E4,-1,1);
                }
            }
            if ((animationStage)>10 && (animationStage)<14) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(0xE);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                aiCardTimer=RecordedRange(60,120)
                           -static_cast<int>(g_OptionsModeAt006714D0)*20;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityY=16.5f;
                field05C=0.15f;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x38B,x,
                    (*(&y))+g_CloudShotYAt006591E4,
                    facing,1);
                PlaySound(0x15);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<10) {
                ResetSecondaryCounter(5);
                ++scriptCounterF00;
                if ((scriptCounterF00)==4) PlaySound(0x13);
            }
            if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<5) {
                ResetSecondaryCounter(8);
                ++scriptCounterF00;
            }
            break;
        }
