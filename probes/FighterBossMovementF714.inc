// F714: original physical native 00543210 action 2DC, complete 602B/169-x86.
// Real bounded handler: startup, floor motion, two native 0x333/0x387
// float projectiles, difficulty gate, terminal counter and state 4.
// Source-backed nonexact giant; never accept this as a whole game function.
        case 0x2DC: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0 && (scriptCounterF00)==0) {
                remainingHits=1;
                collisionResult=0;
                scriptCounterF00=1;
                PlaySound(11);
                velocityY=-10.0f;
                velocityX=30.0f;
                field05C=0.8f;
            }
            if ((animationStage)<4 && y>FloatConstants::Zero) {
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(4);
                    y=0.0f;
                    velocityY=0.0f;
                    field05C=0.0f;
                    break;
                }
            }
            if ((animationStage)<4) {
                SpawnBattleEffect(0x333,
                    float(facing*62)+(x),
                    (*(&y))+GeometryConstants::EightyThree,
                    facing,1);
                if (g_OptionsModeAt006714D0>1)
                    SpawnBattleEffect(0x387,
                        float(facing*62)+(x),
                        (*(&y))+GeometryConstants::EightyThree,
                        facing,1);
            }
            if ((animationStage)>3 && (velocityX)>FloatConstants::Zero) {
                velocityX=(velocityX)-FloatConstants::One;
                if ((velocityX)<FloatConstants::Zero)
                    velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                aiCardTimer=static_cast<short>(RecordedRange(100,180)
                    -static_cast<int>(g_OptionsModeAt006714D0)*30);
            }
            if ((animationFrame)==0)
                collisionResult=0;
            if ((animationStage)==4 && (animationFrame)==0)
                ResetSecondaryCounter(0);
            break;
        }
