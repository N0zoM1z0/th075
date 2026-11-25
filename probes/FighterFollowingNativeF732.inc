// F732: complete native 1FA/1FB/1FE/1FF case interiors in one whole boss.
// Native original 0054B9F9..0054C18F: 1942 CODE B/562 x86/52 physical fields.
// Unlike historical F666 diagnostic source, 1FE/1FF real clamp must use
// strict (velocityX) < 00657CF8, emitting native TEST AH,5; JP (not >= AH1; JNE).
// New preceding authentic real-source stack local allocation naturally
// widens 1FA original ordinal 16/17 EBP scratch from old 3B to native 6B.
// The actual EBP slot and register phase still mismatch; whole 58KB NONEXACT.
// Original `FighterPrecedingStageGrammarF666.inc` retained as earlier evidence.
        case 0x1FA: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=-5.0f;
                velocityY=static_cast<float>((scriptCounterF00)==1)*FloatConstants::Five+GeometryConstants::Fifteen;
                field05C=-0.8f;
                collisionResult=0;
                field3AC=0;
            }
            if (y>FloatConstants::Zero && (animationStage)<8) {
                velocityY=velocityY+field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    ResetSecondaryCounter(8);
                    y=0.0f;
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==8 && (animationFrame)==0) ResetSecondaryCounter(6);
            break;
        }
        case 0x1FB: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)<8 && y>FloatConstants::Zero && (animationStage)>2)
                velocityY=velocityY-FloatConstants::One;
            if ((animationStage)==10) {
                if (collisionResult!=0 && collisionResult!=3 && collisionResult!=1) {
                    ResetPrimaryCounters(0x1FA);
                    break;
                }
                if (y+velocityY<=FloatConstants::Zero) {
                    velocityY=0.0f;
                    velocityX=(velocityX)*FloatConstants::ThreeTenths;
                    ResetSecondaryCounter(0xB);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>10) {
                velocityX=(velocityX)-FloatConstants::OneAndHalf;
                if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                SpawnAuxEffect(0x3C,x,y,
                    facing,1);
                velocityY=22.0f;
                field05C=0.7f;
            }
            if ((animationStage)==8 && (animationFrame)==0) ClearMotionFields();
            if ((animationStage)==10 && (animationFrame)==0) {
                if ((scriptCounterF00)<1) {
                    ResetSecondaryCounter(8);
                    ++scriptCounterF00;
                    break;
                }
                velocityX=20.0f;
                velocityY=-20.0f;
            }
            if ((animationStage)==11 && (animationFrame)==0) ResetSecondaryCounter(9);
            break;
        }
        case 0x1FE: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)<18 && y>FloatConstants::Zero && (animationStage)>7) {
                velocityX=(velocityX)-FloatConstants::ThirtyFiveHundredths;
                velocityY=velocityY-field05C;
                if ((velocityX)<FloatConstants::Three) velocityX=3.0f;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(18);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                SpawnAuxEffect(0x3C,x,y,
                        facing,1);
                PlaySound(4);
                velocityY=6.0f;
                velocityX=4.5f;
                field05C=0.65f;
                SpawnBattleEffect(0x33A,x,y,
                        facing,1);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<0) {
                ResetSecondaryCounter(4);
                ++scriptCounterF00;
                break;
            }
            if ((animationStage)==18 && (animationFrame)==0)
                ResetSecondaryCounter(16);
            break;
        }
        case 0x1FF: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)<22 && y>FloatConstants::Zero && (animationStage)>12) {
                velocityX=(velocityX)-FloatConstants::ThirtyFiveHundredths;
                velocityY=velocityY-field05C;
                if ((velocityX)<FloatConstants::Three) velocityX=3.0f;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(22);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PlaySound(4);
                SpawnAuxEffect(0x3C,x,y,
                        facing,1);
                velocityY=8.0f;
                velocityX=12.0f;
                field05C=0.5f;
                SpawnBattleEffect(0x33A,x,y,
                        facing,1);
            }
            if ((animationStage)==12 && (animationFrame)==0 && (scriptCounterF00)<0) {
                ResetSecondaryCounter(8);
                ++scriptCounterF00;
                break;
            }
            if ((animationStage)==22 && (animationFrame)==0)
                ResetSecondaryCounter(20);
            break;
        }
