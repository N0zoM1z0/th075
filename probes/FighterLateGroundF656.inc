// F656: physical original native 0x131 ground/recovery stages in nonexact giant 00543210.
        case 0x131: {
            velocityY=velocityY-field05C;
            if (y+velocityY<=FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y=0.0f;
                field05C=0.0f;
                velocityY=0.0f;
                break;
            }
            if ((animationStage)==0 && (animationFrame)==0) {
                remainingHits=1;
                collisionResult=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
            if ((animationStage)==3 && (animationFrame)==0) PlaySharedSound(0x1C);
            if ((animationStage)==5 && (animationFrame)==0) {
                remainingHits=1;
                collisionResult=0;
            }
            if ((animationStage)==6 && (animationFrame)==0) PlaySharedSound(0x1D);
            break;
        }
