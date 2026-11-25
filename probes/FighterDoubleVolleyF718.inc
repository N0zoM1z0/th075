// F718: complete physical 00543210 action 2DD /2DE original native source.
// 2DD 0054EAAB..0054ED53: 680 B /189 native x86.
// 2DE 0054ED53..0054EFE7: 660 B /189 native x86.
// Native behavioral branches and typed PE calls retained; whole giant NONEXACT.
        case 0x2DD: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0 && (scriptCounterF00)==0) {
                ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                field3AC=0;
                PlaySound(11);
                velocityY=10.0f;
                velocityX=30.0f;
                verticalAcceleration=0.45f;
                scriptCounterF00=1;
            }
            if ((animationStage)<9 && y>FloatConstants::Zero && (animationStage)>3) {
                velocityX=(velocityX)-FloatConstants::OneAndHalf;
                velocityY=velocityY-verticalAcceleration;
                if ((velocityX)<FloatConstants::Two)
                    velocityX=2.0f;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(9);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if ((animationStage)<4) {
                SpawnBattleEffect(0x329,
                    float(facing*62)+(x),
                    (*(&y))+GeometryConstants::EightyThree,
                    facing,1);
                SpawnBattleEffect(0x387,
                    float(facing*62)+(x),
                    (*(&y))+GeometryConstants::EightyThree,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                aiCardTimer=static_cast<short>(RecordedRange(100,180)
                      -static_cast<int>(g_OptionsModeAt006714D0)*30);
            }
            if ((animationFrame)==0)
                collisionResult=0;
            if ((animationStage)==4 && (animationFrame)==0 && (scriptCounterF00)<4) {
                ResetSecondaryCounter(0);
                ++scriptCounterF00;
                break;
            }
            if ((animationStage)==9 && (animationFrame)==0)
                ResetSecondaryCounter(7);
            break;
        }
        case 0x2DE: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                remainingHits=99;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)<25 && y>FloatConstants::Zero && (animationStage)>14) {
                velocityX=(velocityX)-FloatConstants::FourFifths;
                velocityY=velocityY-verticalAcceleration;
                if ((velocityX)<FloatConstants::Three)
                    velocityX=3.0f;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(25);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                aiCardTimer=static_cast<short>(RecordedRange(100,180)
                      -static_cast<int>(g_OptionsModeAt006714D0)*30);
            }
            if ((animationFrame)==0)
                collisionResult=0;
            if ((animationStage)==7 && (animationFrame)==0) {
                SpawnAuxEffect(0x3C,x,y,
                    facing,1);
                PlaySound(11);
                velocityY=9.0f;
                velocityX=20.0f;
                verticalAcceleration=0.8f;
            }
            if ((animationStage)>6 && (animationStage)<16) {
                SpawnBattleEffect(0x329,
                    float(facing*62)+(x),
                    (*(&y))+GeometryConstants::EightyThree,
                    facing,1);
            }
            if ((animationStage)==16 && (animationFrame)==0 && (scriptCounterF00)<3) {
                ResetSecondaryCounter(12);
                ++scriptCounterF00;
                break;
            }
            if ((animationStage)==25 && (animationFrame)==0)
                ResetSecondaryCounter(23);
            break;
        }
