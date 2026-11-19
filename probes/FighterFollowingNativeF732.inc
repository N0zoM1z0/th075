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
                velocityY=static_cast<float>((reinterpret_cast<signed short&>(scriptCounterF00))==1)*g_FloatMulAt00657874+g_FloatAddAt00657CBC;
                field05C=-0.8f;
                field07C=0;
                field3AC=0;
            }
            if (y>g_ThresholdAt0065782C && (animationStage)<8) {
                velocityY=velocityY+field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    SetAuxActionAt40FB40(8);
                    y=0.0f;
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==8 && (animationFrame)==0) SetAuxActionAt40FB40(6);
            break;
        }
        case 0x1FB: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)<8 && y>g_ThresholdAt0065782C && (animationStage)>2)
                velocityY=velocityY-g_RisingGravityAt0065747C;
            if ((animationStage)==10) {
                if (field07C!=0 && field07C!=3 && field07C!=1) {
                    ResetPrimaryCounters(0x1FA);
                    break;
                }
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    velocityY=0.0f;
                    velocityX=(velocityX)*g_BounceScaleAt006583FC;
                    SetAuxActionAt40FB40(0xB);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>10) {
                velocityX=(velocityX)-g_RisingDragAt006581E0;
                if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
                velocityY=22.0f;
                field05C=0.7f;
            }
            if ((animationStage)==8 && (animationFrame)==0) ClearMotionFields();
            if ((animationStage)==10 && (animationFrame)==0) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<1) {
                    SetAuxActionAt40FB40(8);
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    break;
                }
                velocityX=20.0f;
                velocityY=-20.0f;
            }
            if ((animationStage)==11 && (animationFrame)==0) SetAuxActionAt40FB40(9);
            break;
        }
        case 0x1FE: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)<18 && y>g_ThresholdAt0065782C && (animationStage)>7) {
                velocityX=(velocityX)-g_ShotPositiveDragAt00659A10;
                velocityY=velocityY-field05C;
                if ((velocityX)<g_SpeedClampAt00657CF8) velocityX=3.0f;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(18);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                        facing,1);
                PlaySound(4);
                velocityY=6.0f;
                velocityX=4.5f;
                field05C=0.65f;
                SpawnDirectedAt453A70(0x33A,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                        facing,1);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<0) {
                SetAuxActionAt40FB40(4);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                break;
            }
            if ((animationStage)==18 && (animationFrame)==0)
                SetAuxActionAt40FB40(16);
            break;
        }
        case 0x1FF: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)<22 && y>g_ThresholdAt0065782C && (animationStage)>12) {
                velocityX=(velocityX)-g_ShotPositiveDragAt00659A10;
                velocityY=velocityY-field05C;
                if ((velocityX)<g_SpeedClampAt00657CF8) velocityX=3.0f;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(22);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PlaySound(4);
                SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                        facing,1);
                velocityY=8.0f;
                velocityX=12.0f;
                field05C=0.5f;
                SpawnDirectedAt453A70(0x33A,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                        facing,1);
            }
            if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<0) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                break;
            }
            if ((animationStage)==22 && (animationFrame)==0)
                SetAuxActionAt40FB40(20);
            break;
        }
