// F672: original fighter 00543210 full native 259..25D C++ case grammar.
// These five complete original source bodies remain NONSTRICT from real
// EBP integer-to-float scratch slot differences. Do NOT count exact.
// 259 contains eight original 321/322 shots; 25A..25D each one shot.
// Original PE global 00658264 is shared by 259 and 25B.
        case 0x259: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                UpdateGaugeTimer(250);
                field314=-10.0f;
                SpawnBattleEffect(0x321,
                    float(facing*40)+(x),
                    (*(&y))+GeometryConstants::HundredFifty,
                    facing,1);
                SpawnBattleEffect(0x322,
                    float(facing*40)+(x),
                    (*(&y))+GeometryConstants::HundredFifty,
                    facing,1);
                field314=10.0f;
                SpawnBattleEffect(0x321,
                    float(facing*40)+(x),
                    (*(&y))+GeometryConstants::Sixty,
                    facing,1);
                SpawnBattleEffect(0x322,
                    float(facing*40)+(x),
                    (*(&y))+GeometryConstants::Sixty,
                    facing,1);
                field314=-6.0f;
                SpawnBattleEffect(0x321,
                    float(facing*75)+(x),
                    (*(&y))+g_BarrageY3At0065908C,
                    facing,1);
                SpawnBattleEffect(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_BarrageY3At0065908C,
                    facing,1);
                field314=6.0f;
                SpawnBattleEffect(0x321,
                    float(facing*75)+(x),
                    (*(&y))+GeometryConstants::Eighty,
                    facing,1);
                SpawnBattleEffect(0x322,
                    float(facing*75)+(x),
                    (*(&y))+GeometryConstants::Eighty,
                    facing,1);
            }
            break;
        }
        case 0x25A: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=(velocityX)*FloatConstants::Quarter;
                velocityY=(*(&velocityY))*FloatConstants::Quarter;
                field07C=1;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x32B,
                    float(facing*100)+(x),
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
            break;
        }
        case 0x25B: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=(velocityX)*FloatConstants::Quarter;
                velocityY=(*(&velocityY))*FloatConstants::Quarter;
                field07C=1;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x32D,
                    float(facing*100)+(x),
                    (*(&y))+GeometryConstants::Sixty,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
            break;
        }
        case 0x25C: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x332,
                    float(facing*70)+(x),
                    (*(&y))+g_OneShotYAt0065928C,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            break;
        }
        case 0x25D: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x333,
                    float(facing*70)+(x),
                    (*(&y))+g_OneShotYAt0065928C,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            break;
        }
