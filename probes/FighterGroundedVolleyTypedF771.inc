// F771: complete original 2FB 647-B inner gameplay source, native
// X/Y borrowed floats recover original MOV/FLD angle argument order.
// Still 111 real wrong GPR/operand bytes: NOT a whole-function match.
// F696: real action 0x2FB in the original 00543210 whole fighter parent.
// Native extent 00550D97..0055101E: 181 x86 instructions / 647 CODE bytes.
// Native ground contact, one angled 391 projectile, a real indexed 392
// volley, and completion/phase transitions. Whole parent is NOT exact.
        case 0x2FB: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                fieldF04=0;
                velocityX=15.0f;
                velocityY=10.0f;
                field05C=0.3f;
            }
            if ((animationStage)<18) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0x12);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if ((animationStage)==11 && (animationFrame)==0) {
                PrepareActionAt453D40(0x12);
                field314=CalculateAngleAt483300(
                    reinterpret_cast<const FighterBorrowedXYViewF771*>(opponent)->yAt48-y,
                    (reinterpret_cast<const FighterBorrowedXYViewF771*>(opponent)->xAt44-reinterpret_cast<FighterBorrowedXYViewF771*>(this)->xAt44)
                        *static_cast<float>(facing))
                    /g_StormAngleDenominatorAt00657828;
                SpawnFloatXYAt453A70(0x391,
                    float(facing*30)+(x),
                    (*(&y))+g_StormAngleShotYAt00659A18,
                    facing,1);
                for (int i=0;i<static_cast<int>(g_CloudOpponentAt006714D0)*2+2;++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(facing*36)+(x),
                        (*(&y))+g_StormYAt0065948C,
                        facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070))
                SetNativeActionAt40FAC0(0);
            if ((animationStage)==13 && (animationFrame)==0 &&
                (reinterpret_cast<signed short&>(scriptCounterF00))<static_cast<int>(g_CloudOpponentAt006714D0)+3) {
                SetAuxActionAt40FB40(0xB);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((animationStage)==18 && (animationFrame)==0)
                SetAuxActionAt40FB40(0x10);
            break;
        }
