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
                reinterpret_cast<signed short&>(scriptCounterF00)=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                reinterpret_cast<signed short&>(scriptCounterF00)=2;
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
                    reinterpret_cast<signed short&>(fieldEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==3) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(4);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0x62);
                if (U8(0x3CF)==0)
                    SetNativeActionAt40FAC0(0x63);
            } else if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityX=static_cast<float>(static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF00)))*g_F748_SpeedScaleAt006590B8;
                velocityY=static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF02)))*g_F748_SpeedScaleAt006590B8;
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
                reinterpret_cast<signed short&>(scriptCounterF00)=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0))
                reinterpret_cast<signed short&>(scriptCounterF00)=2;
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
                    reinterpret_cast<signed short&>(fieldEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<5) {
                velocityY=velocityY-field05C;
                if (velocityY+y<g_ThresholdAt0065782C) {
                    y=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(5);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0x62);
                if (U8(0x3CF)==0)
                    SetNativeActionAt40FAC0(0x63);
            } else if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityX=static_cast<float>(static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF00)))*g_F748_SpeedScaleAt006590B8;
                velocityY=static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF02)))*g_F748_SpeedScaleAt006590B8;
                field05C=2.0f;
            }
            break;
        }
