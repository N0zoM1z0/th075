// F657: original fighter 00543210 physical stage 0x186..0x189 source grammar.
// Action 0x186 is deliberately still NONSTRICT (two original EBP−0x84
// temporary slots compile at EBP−0x20). Do not claim whole 186 exact.
// Three following full original native 187/188/189 cases are strictly
// compared against genuine original PE/typed COFF in the full parent.
        case 0x186: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                velocityX=10.0f;
            }
            if ((animationStage)>0) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                SetCameraShake(2.0f);
                SpawnBattleEffect(0x325,
                    float(facing*170)+(x),
                    (y)-GeometryConstants::Six,
                    facing,0);
            }
            break;
        }
        case 0x187: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                velocityX=10.0f;
            }
            if ((animationStage)>0) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            break;
        }
        case 0x188: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                velocityX=15.0f;
            }
            if ((animationStage)>0) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(2);
            break;
        }
        case 0x189: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field3AC=0;
                remainingHits=1;
                collisionResult=0;
                field05C=0.0f;
                velocityY=0.0f;
                velocityX=15.0f;
            }
            if ((velocityX)>FloatConstants::Zero) velocityX=(velocityX)-FloatConstants::OneTwentieth;
            if (y>FloatConstants::Zero && (animationStage)>6 && (animationStage)<9) {
                velocityY=velocityY-field05C;
                if (velocityY+y<=FloatConstants::Zero) {
                    velocityX=0.0f;
                    velocityY=0.0f;
                    field05C=0.0f;
                    y=0.0f;
                    animationFrame=0;
                    ResetSecondaryCounter(9);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==7 && (animationFrame)==0) {
                velocityY=9.0f;
                field05C=0.9f;
            }
            if ((animationStage)==9 && y>FloatConstants::Zero)
                ResetSecondaryCounter((animationStage)-2);
            break;
        }
