// F942: two genuine original 004AC040 resource/burst actions 0x60/0x61
// each 553 original CODE bytes /158 x86 /10 PE global or call fields.
// Original stage 2 < frame < 6, auxiliary action6 and initialization
// stage3 independently read from the SHA-pinned native game PE.
// This C++ is only an internal fragment of the still NONEXACT 82KB
// original fighter. Never credit it as a whole independent function.
// F748 genuine original 00543210 C++ resource-ten-volley actions.
// 060 native 0054559F..005457BC 541 B/154 original x86,
// 061 native 005457BC..005459E5 553 B/158 original x86.
// Source is full meaningful case semantics within ONE 58KB giant,
// not whole-function byte-exact CODE or a stand-alone function.
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
                if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
                    reinterpret_cast<signed short&>(fieldEFA)=0;
                    SpawnBattleEffect(0x3E3,x,y,1,1);
                }
            }
            if ((animationStage)>2 && (animationStage)<6) {
                velocityY=velocityY-field05C;
                if (velocityY+y<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(6);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0x62);
                if ((reinterpret_cast<unsigned char&>(field3CF))==0)
                    ResetPrimaryCounters(0x63);
            } else if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=static_cast<float>(static_cast<int>(scriptCounterF00))*g_F748_SpeedScaleAt006590B8;
                velocityY=static_cast<float>(-static_cast<int>(scriptCounterF02))*g_F748_SpeedScaleAt006590B8;
                field05C=2.0f;
            }
            break;
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
                if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
                    reinterpret_cast<signed short&>(fieldEFA)=0;
                    SpawnBattleEffect(0x3E3,x,y,1,1);
                }
            }
            if ((animationStage)>2 && (animationStage)<6) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(6);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0x62);
                if ((reinterpret_cast<unsigned char&>(field3CF))==0)
                    ResetPrimaryCounters(0x63);
            } else if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=static_cast<float>(static_cast<int>(scriptCounterF00))*g_F748_SpeedScaleAt006590B8;
                velocityY=static_cast<float>(-static_cast<int>(scriptCounterF02))*g_F748_SpeedScaleAt006590B8;
                field05C=2.0f;
            }
            break;
        }
