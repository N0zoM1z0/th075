// F664 original selected giant 00543210: full physical native action 0x200/0x201.
// Ordinary VC7.1 C++ native source interiors; enclosing whole giant remains
// NONEXACT; its effect dispatch uses the inherited Fighter::SpawnAuxEffect ABI.
// Original position +0x44/+0x48 is passed as DWORD bits, never implicit
// FLD/FSTP by-value float conversions in this source grammar.
        case 0x200: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)>7) {
                velocityX=(velocityX)-FloatConstants::NineTenths;
                if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
            }
            if ((animationStage)==7 && collisionResult==2) {
                ResetSecondaryCounter(8);
                velocityX=10.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(7);
                SpawnAuxEffect(0x3C,x,y,
                    facing,1);
            }
            if ((animationStage)==7 && (animationFrame)==0) velocityX=50.0f;
            if ((animationStage)==8 && (animationFrame)==0) velocityX=10.0f;

            break;
        }
        case 0x201: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                remainingHits=1;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)>7) {
                velocityX=(velocityX)-FloatConstants::NineTenths;
                if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
            }
            if ((animationStage)==7 && collisionResult==2) {
                ResetSecondaryCounter(8);
                velocityX=10.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(7);
                SpawnAuxEffect(0x3C,x,y,
                    facing,1);
            }
            if ((animationStage)==7 && (animationFrame)==0) velocityX=50.0f;
            if ((animationStage)==8 && (animationFrame)==0) velocityX=10.0f;
            if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)==0) {
                ++scriptCounterF00;
                ResetSecondaryCounter(2);
                collisionResult=0;
                remainingHits=1;
            }
            break;
        }
