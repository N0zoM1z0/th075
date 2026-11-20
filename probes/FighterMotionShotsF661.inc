// F661: actual original fighter 00543210 native shot cases 0x18A/0x18B.
// Full parent ordinary VC7.1 C++ source grammar, still NONSTRICT.
// FILD scratch operands remain genuinely nonexact against original native
// EBP-0x88 and EBP-0x8C. Do NOT credit either as strict native interior.
        case 0x18A: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field080=1;
                field07C=0;
                velocityX=15.0f;
                scriptCounterF00=0;
            }
            velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
            if ((velocityX)<g_ThresholdAt0065782C) {
                velocityX=0.0f;
                field3AC=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnBattleEffect(0x327,
                    float(facing*151)+(x),
                    (y)+g_YPlusAt0065929C,
                    facing,1);
            }
            break;
        }
        case 0x18B: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field080=1;
                field07C=0;
                velocityX=10.0f;
                scriptCounterF00=0;
            }
            if ((animationStage)>6) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(2);
            if ((animationStage)==7 && (animationFrame)==0 && (scriptCounterF00)<2) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
                field080=1;
                field07C=0;
            }
            if ((animationStage)==6 && (animationFrame)==0) {
                SpawnBattleEffect(0x328,
                    float(facing*128)+(x),
                    (y)+g_YPlusAt00658400,
                    facing,1);
            }
            break;
        }
