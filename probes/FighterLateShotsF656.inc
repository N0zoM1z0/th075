// F656: true original native 0x133..0x136 stage-specific movement and shots.
        case 0x133: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=0.0f;
                velocityY=0.0f;
                verticalAcceleration=0.0f;
                remainingHits=1;
                collisionResult=0;
            }
            if ((velocityX)>FloatConstants::Zero)
                velocityX=(velocityX)-FloatConstants::OneAndHalf;
            if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PlaySharedSound(0x1C);
                SpawnBattleEffect(0x341,x,y,
                    facing,1);
            }
            if ((animationStage)==6 && (animationFrame)==0) velocityX=15.0f;
            if ((animationStage)==8 && (animationFrame)==0) {
                PlaySharedSound(0x1C);
                remainingHits=1;
                collisionResult=0;
                SpawnBattleEffect(0x342,x,y,
                    facing,1);
            }
            break;
        }
        case 0x134: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
            }
            if ((field3AC)>0) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                scriptCounterF00=0;
            }
            if ((animationStage)==1 && (animationFrame)==0) PlaySharedSound(0x1D);
            break;
        }
        case 0x135: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
            }
            if ((field3AC)>0) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if ((animationStage)==10 || (animationStage)==11) {
                velocityX=(velocityX)-FloatConstants::Half;
                if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                scriptCounterF00=0;
            }
            if ((animationStage)==7 && (animationFrame)==0) velocityX=20.0f;
            if ((animationStage)==10 && (animationFrame)==0)
                SpawnBattleEffect(0x33F,x,y,
                    facing,1);
            break;
        }
        case 0x136: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
            }
            if ((field3AC)>0) {
                velocityX=(velocityX)-FloatConstants::ThreeFifths;
                if ((velocityX)<FloatConstants::Zero) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0)
                SpawnBattleEffect(0x33E,x,y,
                    facing,1);
            if ((animationStage)==6 && (animationFrame)==0) PlaySharedSound(0x1D);
            break;
        }
