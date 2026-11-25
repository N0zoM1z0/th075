// F661: actual original fighter 00543210 native shot cases 0x18A/0x18B.
// Full parent ordinary VC7.1 C++ source grammar, still NONSTRICT.
// FILD scratch operands remain genuinely nonexact against original native
// EBP-0x88 and EBP-0x8C. Do NOT credit either as strict native interior.
        case 0x18A: {
            if ((animationStage)==0 && (animationFrame)==0) {
                remainingHits=1;
                collisionResult=0;
                velocityX=15.0f;
                scriptCounterF00=0;
            }
            velocityX=(velocityX)-FloatConstants::ThreeFifths;
            if ((velocityX)<FloatConstants::Zero) {
                velocityX=0.0f;
                field3AC=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x327,
                    float(facing*151)+(x),
                    (y)+GeometryConstants::HundredFour,
                    facing,1);
            }
            break;
        }
        case 0x18B: {
            if ((animationStage)==0 && (animationFrame)==0) {
                remainingHits=1;
                collisionResult=0;
                velocityX=10.0f;
                scriptCounterF00=0;
            }
            if ((animationStage)>6) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(2);
            if ((animationStage)==7 && (animationFrame)==0 && (scriptCounterF00)<2) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
                remainingHits=1;
                collisionResult=0;
            }
            if ((animationStage)==6 && (animationFrame)==0) {
                SpawnBattleEffect(0x328,
                    float(facing*128)+(x),
                    (y)+GeometryConstants::Seventy,
                    facing,1);
            }
            break;
        }
