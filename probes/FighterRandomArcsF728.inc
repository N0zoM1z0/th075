// F728: two complete physical 00543210 original random-arc game actions.
// 1F4: 0054A6CC..0054A8E6, 538 native CODE B /149 x86.
// 1F5: 0054A8E6..0054AB00, 538 native CODE B /149 x86.
// Member Y is deliberately read via a genuine lvalue before the native
// 00657858 FADD: VC7.1 now owns the original DIR32 at x86 ordinal
// 36/55, not a source-only FLD of the global before member FADD.
// All four x87 intermediate stack owners remain NONEXACT in each case.
// Full real float shot/motion/ground/action source, whole giant NONEXACT.
        case 0x1F4: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
            }
            if (RandomBoundaryAt455580(0,100)<40 && (animationStage)>3 && (animationStage)<8) {
                SpawnFloatXYAt453A70(0x330,
                    ((x)+g_F728_RandomOffsetXAt00657878)
                        -float(RandomBoundaryAt455580(0,60)),
                    ((*(&y))+g_F728_RandomOffsetYAt00657858)
                        +float(RandomBoundaryAt455580(0,140)),
                    facing,1);
            }
            if ((velocityX)>g_ThresholdAt0065782C) {
                velocityX=(velocityX)-g_F728_PositiveDragAt006583FC;
                if ((velocityX)<g_ThresholdAt0065782C)
                    velocityX=0.0f;
            }
            if (y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    SetAuxActionAt40FB40(12);
                    y=0.0f;
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070))
                ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(4);
                velocityX=8.0f;
                velocityY=14.0f;
                field05C=0.8f;
            }
            if ((animationStage)==18 && (animationFrame)==0)
                SetAuxActionAt40FB40(16);
            break;
        }
        case 0x1F5: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
            }
            if ((velocityX)>g_ThresholdAt0065782C) {
                velocityX=(velocityX)-g_F728_PositiveDrag2At00658058;
                if ((velocityX)<g_ThresholdAt0065782C)
                    velocityX=0.0f;
            }
            if (RandomBoundaryAt455580(0,100)<40 && (animationStage)>3 && (animationStage)<8) {
                SpawnFloatXYAt453A70(0x330,
                    ((x)+g_F728_RandomOffsetXAt00657878)
                        -float(RandomBoundaryAt455580(0,60)),
                    ((*(&y))+g_F728_RandomOffsetYAt00657858)
                        +float(RandomBoundaryAt455580(0,140)),
                    facing,1);
            }
            if (y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    SetAuxActionAt40FB40(12);
                    y=0.0f;
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070))
                ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(4);
                velocityX=18.0f;
                velocityY=16.0f;
                field05C=0.8f;
            }
            if ((animationStage)==12 && (animationFrame)==0)
                SetAuxActionAt40FB40(10);
            break;
        }
