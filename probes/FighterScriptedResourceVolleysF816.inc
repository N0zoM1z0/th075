// F816: original Japanese TH075 scripted fighter 005214B0 actions
// 0x60 and 0x61 are each 586 complete native interior CODE B /169 x86,
// not separate callable original functions. Real original signed contact
// threshold is strict <, both ground resets use auxiliary action 4,
// and stage-four continuation is inside the getter-negative else body.
// Real native game cases each exit DIRECTLY to the encompassing
// function epilogue: their ordinary C++ return is semantically correct
// because the enclosing original switch has no further work afterward.
// Each ten-projectile loop's index is used by real original gameplay;
// it naturally restores the native EBP-0x10 saved this in its full parent.
        case 0x60: {
            if (static_cast<int>(facing) * inputX>0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                scriptCounterF00=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                scriptCounterF00=2;
            if ((animationStage)==0 && (animationFrame)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnBattleEffect(0x3E4,x,y,1,1);
                if ((fieldEFA)>25) {
                    fieldEFA=0;
                    SpawnBattleEffect(0x3E3,x,y,1,1);
                }
            }
            if ((animationStage)==3 || (animationStage)==2) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(4);
                    return;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0x62);
                if ((field3CF)==0)
                    ResetPrimaryCounters(0x63);
            } else {
                if ((animationStage)==2 && (animationFrame)==0) {
                    velocityX=static_cast<float>(scriptCounterF00)*g_F748_SpeedScaleAt006590B8;
                    velocityY=static_cast<float>(-scriptCounterF02)*g_F748_SpeedScaleAt006590B8;
                    field05C=2.0f;
                }
                if ((animationStage)==4 && (animationFrame)==0)
                    ResetSecondaryCounter(3);
            }
            return;
        }

        case 0x61: {
            if (static_cast<int>(facing) * inputX>0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                scriptCounterF00=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                scriptCounterF00=2;
            if ((animationStage)==0 && (animationFrame)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnBattleEffect(0x3E4,x,y,1,1);
                if ((fieldEFA)>25) {
                    fieldEFA=0;
                    SpawnBattleEffect(0x3E3,x,y,1,1);
                }
            }
            if ((animationStage)==3 || (animationStage)==2) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(4);
                    return;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0x62);
                if ((field3CF)==0)
                    ResetPrimaryCounters(0x63);
            } else {
                if ((animationStage)==2 && (animationFrame)==0) {
                    velocityX=static_cast<float>(scriptCounterF00)*g_F748_SpeedScaleAt006590B8;
                    velocityY=static_cast<float>(-scriptCounterF02)*g_F748_SpeedScaleAt006590B8;
                    field05C=2.0f;
                }
                if ((animationStage)==4 && (animationFrame)==0)
                    ResetSecondaryCounter(3);
            }
            return;
        }
