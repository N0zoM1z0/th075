// F734: full native physical 00543210 0x190/0x191/0x192 8-shot cases.
// 190 00549364..00549478: 276 native CODE bytes/75 x86.
// 191 00549478..0054958C: 276 native CODE bytes/75 x86.
// 192 0054958C..0054967C: 240 native CODE bytes/68 x86.
// Actual stage/flags/8 volley projectiles and original member calls.
// These interiors are NOT separate original game functions.
        case 0x190: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
                scriptCounterF00=0;
            }
            if (inputC==0)
                scriptCounterF00=1;
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(0);
                field314=0.0f;
                UpdateGaugeTimer(200);
                for (int shot=0; shot<8; ++shot) {
                    SpawnBattleEffect(0x324,
                        float(facing*70)+(x),
                        (*(&y))+g_F734_RoundY0At00659A30,
                        facing,1);
                }
            }
            if (AdvanceNestedFrame()==(field070))
                ResetPrimaryCounters(0);
            break;
        }
        case 0x191: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
                scriptCounterF00=0;
            }
            if (inputC==0)
                scriptCounterF00=1;
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(0);
                field314=20.0f;
                UpdateGaugeTimer(200);
                for (int shot=0; shot<8; ++shot) {
                    SpawnBattleEffect(0x324,
                        float(facing*64)+(x),
                        (*(&y))+g_F734_RoundY1At00659A2C,
                        facing,1);
                }
            }
            if (AdvanceNestedFrame()==(field070))
                ResetPrimaryCounters(0);
            break;
        }
        case 0x192: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(0);
                field314=45.0f;
                UpdateGaugeTimer(200);
                for (int shot=0; shot<8; ++shot) {
                    SpawnBattleEffect(0x324,
                        float(facing*44)+(x),
                        (*(&y))+g_F734_RoundY2At00659A28,
                        facing,1);
                }
            }
            if (AdvanceNestedFrame()==(field070))
                ResetPrimaryCounters(2);
            break;
        }
