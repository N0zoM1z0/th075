// F674: original 00543210 full native action 2EF, 224 x86/788 CODE B.
// Genuine VC7.1 normal C++ within still-NONEXACT giant full parent;
// source method names/signatures are provisional original ABI grammar.
// A REAL subsequent native terminal stage is needed to restore the
// physical original 5-byte shared-exit JMP, not source padding.
        case 0x2EF: {
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                fieldF04=0;
                collisionResult=1;
                ClearMotionFields();
            }
            if ((animationStage)>3 && (animationStage)<11) {
                velocityY=velocityY-FloatConstants::NinetyFiveHundredths;
                if (velocityY<FloatConstants::Zero) velocityY=0.0f;
            }
            if ((animationStage)>4 && (animationStage)<8) {
                ++scriptCounterF02;
                ++fieldF04;
                if ((scriptCounterF02)>100-static_cast<int>(g_OptionsModeAt006714D0)*20) {
                    scriptCounterF02=0;
                    PlaySound(0x10);
                    SpawnBattleEffect(0x389,x,
                        (*(&y))+GeometryConstants::TwoHundredFifty,
                        facing,1);
                    SpawnBattleEffect(0x38A,x,
                        (*(&y))+GeometryConstants::TwoHundredFifty,
                        facing,1);
                }
            }
            if ((animationStage)>10 && (animationStage)<14) {
                velocityY=velocityY-verticalAcceleration;
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
                velocityY=16.5f;
                verticalAcceleration=0.15f;
                PlaySound(0x15);
            }
            if ((animationStage)==5 && (animationFrame)==0)
                SpawnBattleEffect(0x38B,x,
                    (*(&y))+GeometryConstants::TwoHundredFifty,
                    facing,1);
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<25) {
                ResetSecondaryCounter(5);
                ++scriptCounterF00;
            }
            if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<25) {
                ResetSecondaryCounter(8);
                ++scriptCounterF00;
            }
            break;
        }
