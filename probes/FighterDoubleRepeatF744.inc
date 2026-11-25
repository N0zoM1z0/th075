// F744: genuinely used ordinary C++ for two COMPLETE original physical
// actions in enclosing 00543210 giant, NOT separate authored functions.
// 19A 00549D5C..00549FBB 607 native CODE B/166 x86;
// 19B 00549FBB..0054A21A 607 native CODE B/166 x86.
// Native stage, gravity, ground, two authentic 0x330 shots per action.
        case 0x19A: {
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                collisionResult=1;
                velocityX=(velocityX)*FloatConstants::Quarter;
                velocityY=(*(&velocityY))*FloatConstants::Quarter;
            }
            if ((animationStage)>5) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    y=0.0f;
                    ResetPrimaryCounters(10);
                    break;
                }
            }
            if (y+velocityY<=FloatConstants::Zero) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(9);
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(2);
                field314=0.0f;
                SpawnBattleEffect(0x330,
                    float(facing*35)+(x),
                    (*(&y))+g_F737_RoundY0At00659A24,
                    facing,1);
                UpdateGaugeTimer(100);
            }
            if ((animationStage)==5 && (animationFrame)==0
                    && static_cast<unsigned int>(inputA)>0
                    && (scriptCounterF00)<6 && (spirit)>0) {
                PlaySound(2);
                field314=0.0f;
                SpawnBattleEffect(0x330,
                    float(facing*35)+(x),
                    (*(&y))+g_F737_RoundY0At00659A24,
                    facing,1);
                UpdateGaugeTimer(20);
                ResetSecondaryCounter(4);
                ++scriptCounterF00;
            }
            break;
        }
        case 0x19B: {
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                collisionResult=1;
                velocityX=(velocityX)*FloatConstants::Quarter;
                velocityY=(*(&velocityY))*FloatConstants::Quarter;
            }
            if ((animationStage)>5) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    y=0.0f;
                    ResetPrimaryCounters(10);
                    break;
                }
            }
            if (y+velocityY<=FloatConstants::Zero) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(9);
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(2);
                field314=-20.0f;
                SpawnBattleEffect(0x330,
                    float(facing*27)+(x),
                    (*(&y))+g_F737_RoundY1At00659A20,
                    facing,1);
                UpdateGaugeTimer(100);
            }
            if ((animationStage)==5 && (animationFrame)==0
                    && static_cast<unsigned int>(inputA)>0
                    && (scriptCounterF00)<6 && (spirit)>0) {
                PlaySound(2);
                field314=-20.0f;
                SpawnBattleEffect(0x330,
                    float(facing*27)+(x),
                    (*(&y))+g_F737_RoundY1At00659A20,
                    facing,1);
                UpdateGaugeTimer(20);
                ResetSecondaryCounter(4);
                ++scriptCounterF00;
            }
            break;
        }
