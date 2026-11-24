// F771: complete original 2FB 647-B inner gameplay source, native
// X/Y borrowed floats recover original MOV/FLD angle argument order.
// Still 111 real wrong GPR/operand bytes: NOT a whole-function match.
// F696: real action 0x2FB in the original 00543210 whole fighter parent.
// Native extent 00550D97..0055101E: 181 x86 instructions / 647 CODE bytes.
// Native ground contact, one angled 391 projectile, a real indexed 392
// volley, and completion/phase transitions. Whole parent is NOT exact.
        case 0x2FB: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                fieldF04=0;
                velocityX=15.0f;
                velocityY=10.0f;
                field05C=0.3f;
            }
            if ((animationStage)<18) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(0x12);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if ((animationStage)==11 && (animationFrame)==0) {
                PlaySound(0x12);
                field314=AngleAt00483300(
                    opponent->y-y,
                    (opponent->x-x)
                        *static_cast<float>(facing))
                    /GeometryConstants::RadiansPerDegree;
                SpawnBattleEffect(0x391,
                    float(facing*30)+(x),
                    (*(&y))+GeometryConstants::EightySeven,
                    facing,1);
                for (int i=0;i<static_cast<int>(g_OptionsModeAt006714D0)*2+2;++i)
                    SpawnBattleEffect(0x392,
                        float(facing*36)+(x),
                        (*(&y))+g_StormYAt0065948C,
                        facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if ((animationStage)==13 && (animationFrame)==0 &&
                (scriptCounterF00)<static_cast<int>(g_OptionsModeAt006714D0)+3) {
                ResetSecondaryCounter(0xB);
                ++scriptCounterF00;
            }
            if ((animationStage)==18 && (animationFrame)==0)
                ResetSecondaryCounter(0x10);
            break;
        }
