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
                reinterpret_cast<signed short&>(scriptCounterF00)=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                reinterpret_cast<signed short&>(scriptCounterF00)=2;
            if ((animationStage)==0 && (animationFrame)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
                    reinterpret_cast<signed short&>(fieldEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                }
            }
            if ((animationStage)==3 || (animationStage)==2) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    SetAuxActionAt40FB40(4);
                    return;
                }
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0x62);
                if ((reinterpret_cast<unsigned char&>(field3CF))==0)
                    SetNativeActionAt40FAC0(0x63);
            } else {
                if ((animationStage)==2 && (animationFrame)==0) {
                    velocityX=static_cast<float>(static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF00)))*g_F748_SpeedScaleAt006590B8;
                    velocityY=static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF02)))*g_F748_SpeedScaleAt006590B8;
                    field05C=2.0f;
                }
                if ((animationStage)==4 && (animationFrame)==0)
                    SetAuxActionAt40FB40(3);
            }
            return;
        }

        case 0x61: {
            if (static_cast<int>(facing) * inputX>0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                reinterpret_cast<signed short&>(scriptCounterF00)=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                reinterpret_cast<signed short&>(scriptCounterF00)=2;
            if ((animationStage)==0 && (animationFrame)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
                    reinterpret_cast<signed short&>(fieldEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                }
            }
            if ((animationStage)==3 || (animationStage)==2) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    SetAuxActionAt40FB40(4);
                    return;
                }
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0x62);
                if ((reinterpret_cast<unsigned char&>(field3CF))==0)
                    SetNativeActionAt40FAC0(0x63);
            } else {
                if ((animationStage)==2 && (animationFrame)==0) {
                    velocityX=static_cast<float>(static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF00)))*g_F748_SpeedScaleAt006590B8;
                    velocityY=static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF02)))*g_F748_SpeedScaleAt006590B8;
                    field05C=2.0f;
                }
                if ((animationStage)==4 && (animationFrame)==0)
                    SetAuxActionAt40FB40(3);
            }
            return;
        }
