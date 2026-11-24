// F764: original 2FA full inner action C++ grammar in 00543210.
// Six genuine native predicate/borrowed-float corrections restore original
// 971-B/279-x86 geometry. Remaining 156 register operand bytes NONEXACT.
// F699: reconstruct entire original 00543210 action 0x2FA into normal C++.
// Native physical case 005509CC..00550D97, 279 x86 /971 CODE bytes.
// This is an internal case in a NONEXACT 58KB parent, not a standalone function.
        case 0x2FA: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)<10 && y>FloatConstants::Zero && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-FloatConstants::ThreeFifths;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    ResetPrimaryCounters(10);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>9 && (animationStage)<13 && !CheckHorizontalLimits()) {
                if (facing==1)
                    x=(field2D8)+FloatConstants::Five;
                if (facing==-1)
                    x=(field2DC)-FloatConstants::Five;
            }
            if ((animationStage)>7 && (animationStage)<10 && y>FloatConstants::Zero) {
                if ((CheckHorizontalLimits() && (((x)<GeometryConstants::SixHundredForty
                     && facing==1)
                    || ((x)>GeometryConstants::SixHundredForty
                        && facing==-1)))
                    || (((field2D8)+FloatConstants::Five)>=x
                        && facing==1)
                    || (((field2DC)-FloatConstants::Five)<=x
                        && facing==-1)) {
                    ResetSecondaryCounter(10);
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                if ((scriptCounterF00)<3-static_cast<int>(g_OptionsModeAt006714D0)) {
                    ++scriptCounterF00;
                    ResetSecondaryCounter(12);
                    break;
                }
                ResetPrimaryCounters(0x2FB);
                break;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                if (AbsFloatAt00412D90(x-opponent->x)
                    <GeometryConstants::ThreeHundredTwenty) {
                    if (RecordedRange(0,100)<50)
                        facing=1;
                    else
                        facing=-1;
                }
                PlaySound(5);
                SpawnAuxEffect(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
                SpawnAuxEffect(0x7E,x,
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
                velocityX=-20.0f;
                velocityY=17.5f;
                if (RecordedRange(0,100)<50)
                    velocityY=15.0f;
                field05C=0.8f;
            }
            if ((animationStage)==10 && (animationFrame)==0)
                ResetSecondaryCounter(8);
            break;
        }
