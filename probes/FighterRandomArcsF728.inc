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
                field3AC=0;
            }
            if (RecordedRange(0,100)<40 && (animationStage)>3 && (animationStage)<8) {
                SpawnBattleEffect(0x330,
                    ((x)+GeometryConstants::Thirty)
                        -float(RecordedRange(0,60)),
                    ((*(&y))+GeometryConstants::Forty)
                        +float(RecordedRange(0,140)),
                    facing,1);
            }
            if ((velocityX)>FloatConstants::Zero) {
                velocityX=(velocityX)-FloatConstants::ThreeTenths;
                if ((velocityX)<FloatConstants::Zero)
                    velocityX=0.0f;
            }
            if (y>FloatConstants::Zero) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    ResetSecondaryCounter(12);
                    y=0.0f;
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(4);
                velocityX=8.0f;
                velocityY=14.0f;
                field05C=0.8f;
            }
            if ((animationStage)==18 && (animationFrame)==0)
                ResetSecondaryCounter(16);
            break;
        }
        case 0x1F5: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
            }
            if ((velocityX)>FloatConstants::Zero) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero)
                    velocityX=0.0f;
            }
            if (RecordedRange(0,100)<40 && (animationStage)>3 && (animationStage)<8) {
                SpawnBattleEffect(0x330,
                    ((x)+GeometryConstants::Thirty)
                        -float(RecordedRange(0,60)),
                    ((*(&y))+GeometryConstants::Forty)
                        +float(RecordedRange(0,140)),
                    facing,1);
            }
            if (y>FloatConstants::Zero) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    ResetSecondaryCounter(12);
                    y=0.0f;
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(4);
                velocityX=18.0f;
                velocityY=16.0f;
                field05C=0.8f;
            }
            if ((animationStage)==12 && (animationFrame)==0)
                ResetSecondaryCounter(10);
            break;
        }
