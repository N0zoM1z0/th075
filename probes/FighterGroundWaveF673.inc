// F673: original fighter 00543210 native complete physical case 0x2BC.
// Normal pinned VC7.1 C++ source within a regenerated complete parent;
// no independent whole-function CODE credit, no artificial locals.
// Source method types remain provisional native ABI probes.
        case 0x2BC: {
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                field07C=1;
                ClearMotionFields();
                spellPower=(spellPower)-GeometryConstants::Hundred;
                SetNonnegativeWord(40);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73,x,
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
            }
            if ((animationStage)>3 && (animationStage)<11) {
                velocityY=velocityY-FloatConstants::FortyFiveHundredths;
                if (velocityY<FloatConstants::Zero) velocityY=0.0f;
            }
            if ((animationStage)>10 && (animationStage)<14) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(0xE);
                    break;
                }
            }
            if ((animationStage)==5 && (animationFrame)==0) SetCameraShake(2.0f);
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityY=15.0f;
                field05C=0.85f;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x326,x,0.0f,
                    facing,1);
                SpawnBattleEffect(0x33B,x,0.0f,
                    facing,1);
                UpdateGaugeTimer(500);
                PlaySound(8);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<7) {
                ResetSecondaryCounter(5);
                ++scriptCounterF00;
            }
            if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<9) {
                ResetSecondaryCounter(8);
                ++scriptCounterF00;
            }
            if ((animationStage)==14 && (animationFrame)==0) ResetSecondaryCounter(12);
            break;
        }
