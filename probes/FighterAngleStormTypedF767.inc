// F767: authentic observed borrowed opponent/actor X and read-only Y
// lvalues restore all 381 native 2F9 opcode and widths. Its 249 real
// register/nonfield bytes remain NONEXACT in the 58KB game parent.
// F684: 00543210 original complete 0x2F9 angle-storm source grammar.
// Native 381 genuine x86 /1367 original CODE B /34 actual PE/COFF fields.
// Compiled 381 x86/1319B, 16 original wide EBP integer float temporaries
// and original GPR register roles remain NONSTRICT. Never credit case.
// CalculateAngleAt483300 / __ftol2 are native source ABI probes only.
case 0x2F9: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                fieldF04=0;
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)>1 && (animationStage)<20) {
                if ((animationStage)>15 || (animationStage)<10) {
                    velocityY=velocityY-field05C;
                }
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(0x14);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if ((animationStage)==11 && (animationFrame)==0) {
                PlaySound(0x12);
                field314=float((scriptCounterF02)+(scriptCounterF00)*10);
                SpawnBattleEffect(0x391,
                    float(facing*30)+(x),
                    (*(&y))+g_StormAngleShotYAt00659A18,
                    facing,1);
                for (int i=0;i<static_cast<int>(g_OptionsModeAt006714D0)*2+4;++i)
                    SpawnBattleEffect(0x392,
                        float(facing*30)+(x),
                        (*(&y))+g_StormAngleShotYAt00659A18,
                        facing,1);
            }
            if ((animationStage)==14 && (animationFrame)==0) {
                PlaySound(0x12);
                field314=float((scriptCounterF02)-(scriptCounterF00)*10);
                SpawnBattleEffect(0x391,
                    float(facing*30)+(x),
                    (*(&y))+g_StormAngleShotYAt00659A18,
                    facing,1);
                for (int i=0;i<static_cast<int>(g_OptionsModeAt006714D0)*2+4;++i)
                    SpawnBattleEffect(0x392,
                        float(facing*30)+(x),
                        (*(&y))+g_StormAngleShotYAt00659A18,
                        facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                aiCardTimer=RecordedRange(60,100)
                       -static_cast<int>(g_OptionsModeAt006714D0)*20;
            }
            if ((animationStage)==2 && (animationFrame)==0) {
                velocityY=12.5f;
                velocityX=-8.0f;
                field05C=0.4f;
            }
            if ((animationStage)==10 && (animationFrame)==0) {
                velocityX=(*(&velocityX))*FloatConstants::OneFifth;
                velocityY=(*(&velocityY))*FloatConstants::OneFifth;
            }
            if ((animationStage)==11 && (animationFrame)==0) {
                scriptCounterF02=
                    AngleAt00483300(
                        (*(&(opponent->y))-*(&y)),
                        ((opponent->x-x))
                           *static_cast<float>(facing))
                    /GeometryConstants::RadiansPerDegree;
            }
            if ((animationStage)==13 && (animationFrame)==0) {
                if ((scriptCounterF00)<static_cast<int>(g_OptionsModeAt006714D0)*2+1) {
                    ResetSecondaryCounter(0xB);
                    ++scriptCounterF00;
                } else scriptCounterF00=0;
            }
            if ((animationStage)==14 && (animationFrame)==0) {
                scriptCounterF02=
                    AngleAt00483300(
                        (*(&(opponent->y))-*(&y)),
                        ((opponent->x-x))
                           *static_cast<float>(facing))
                    /GeometryConstants::RadiansPerDegree;
            }
            if ((animationStage)==16 && (animationFrame)==0
                && (scriptCounterF00)<static_cast<int>(g_OptionsModeAt006714D0)*2+1) {
                ResetSecondaryCounter(14);
                ++scriptCounterF00;
            }
            if ((animationStage)==20 && (animationFrame)==0) ResetSecondaryCounter(0x12);
            break;
        }
