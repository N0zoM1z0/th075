// F744: genuinely used ordinary C++ for two COMPLETE original physical
// actions in enclosing 00543210 giant, NOT separate authored functions.
// 19A 00549D5C..00549FBB 607 native CODE B/166 x86;
// 19B 00549FBB..0054A21A 607 native CODE B/166 x86.
// Native stage, gravity, ground, two authentic 0x330 shots per action.
        case 0x19A: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                velocityX=(velocityX)*g_BounceScaleAt00657F74;
                velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>5) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    y=0.0f;
                    SetNativeActionAt40FAC0(10);
                    break;
                }
            }
            if (y+velocityY<=g_ThresholdAt0065782C) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetNativeActionAt40FAC0(9);
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(2);
                field314=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*35)+(x),
                    (*(&y))+g_F737_RoundY0At00659A24,
                    facing,1);
                StartAnimationAt46D000(100);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0
                    && static_cast<unsigned int>(inputA)>0
                    && (reinterpret_cast<signed short&>(scriptCounterF00))<6 && (reinterpret_cast<signed short&>(meter))>0) {
                PrepareActionAt453D40(2);
                field314=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*35)+(x),
                    (*(&y))+g_F737_RoundY0At00659A24,
                    facing,1);
                StartAnimationAt46D000(20);
                SetAuxActionAt40FB40(4);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
        case 0x19B: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                velocityX=(velocityX)*g_BounceScaleAt00657F74;
                velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>5) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    y=0.0f;
                    SetNativeActionAt40FAC0(10);
                    break;
                }
            }
            if (y+velocityY<=g_ThresholdAt0065782C) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetNativeActionAt40FAC0(9);
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(2);
                field314=-20.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*27)+(x),
                    (*(&y))+g_F737_RoundY1At00659A20,
                    facing,1);
                StartAnimationAt46D000(100);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0
                    && static_cast<unsigned int>(inputA)>0
                    && (reinterpret_cast<signed short&>(scriptCounterF00))<6 && (reinterpret_cast<signed short&>(meter))>0) {
                PrepareActionAt453D40(2);
                field314=-20.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*27)+(x),
                    (*(&y))+g_F737_RoundY1At00659A20,
                    facing,1);
                StartAnimationAt46D000(20);
                SetAuxActionAt40FB40(4);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
