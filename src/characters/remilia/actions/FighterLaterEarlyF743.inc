// F743: four real complete native physical actions from ONE original
// 00543210 fighter switch (all still NONEXACT as a 58KB parent).
// Original 19C 0054A21A..0054A2F4 218 B/62 x86;
// 19E 0054A2F4..0054A462 366 B/104 x86;
// 1A0 0054A462..0054A597 309 B/84 x86;
// 1A1 0054A597..0054A6CC 309 B/84 x86.
// Distinct stage, floor/velocity and actual 0x335 shots are NOT stubs.
        case 0x19C: {
            if ((animationStage)==0 && (animationFrame)==0) {
                collisionResult=1;
                ClearMotionFields();
                scriptCounterF00=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(3);
                field314=0.0f;
                SpawnBattleEffect(0x335,
                    float(facing*40)+(x),
                    (*(&y))+g_F743_Y19CAt00659A14,
                    facing,1);
                UpdateGaugeTimer(200);
            }
            break;
        }
        case 0x19E: {
            if ((animationStage)==0 && (animationFrame)==0) {
                collisionResult=1;
                ClearMotionFields();
                scriptCounterF00=0;
            }
            if (y>FloatConstants::Zero) {
                velocityY=velocityY-verticalAcceleration;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    y=0.0f;
                    ResetPrimaryCounters(10);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetSecondaryCounter(10);
            if ((animationStage)==2 && (animationFrame)==0) {
                velocityX=-6.0f;
                velocityY=17.5f;
                verticalAcceleration=0.8f;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(3);
                field314=-20.0f;
                SpawnBattleEffect(0x335,
                    float(facing*27)+(x),
                    (*(&y))+g_F737_RoundY1At00659A20,
                    facing,1);
                UpdateGaugeTimer(200);
            }
            break;
        }
        case 0x1A0: {
            if ((animationStage)==0 && (animationFrame)==0)
                collisionResult=1;
            velocityY=velocityY-verticalAcceleration;
            if (y+velocityY<=FloatConstants::Zero) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(3);
                velocityX=-8.0f;
                velocityY=10.0f;
                verticalAcceleration=0.65f;
                field314=0.0f;
                UpdateGaugeTimer(200);
                SpawnBattleEffect(0x335,
                    float(facing*45)+(x),
                    (*(&y))+GeometryConstants::HundredFifteen,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(9);
            break;
        }
        case 0x1A1: {
            if ((animationStage)==0 && (animationFrame)==0)
                collisionResult=1;
            velocityY=velocityY-verticalAcceleration;
            if (y+velocityY<=FloatConstants::Zero) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                PlaySound(3);
                velocityX=-8.0f;
                velocityY=10.0f;
                verticalAcceleration=0.65f;
                field314=-20.0f;
                UpdateGaugeTimer(200);
                SpawnBattleEffect(0x335,
                    float(facing*27)+(x),
                    (*(&y))+g_F737_RoundY1At00659A20,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(9);
            break;
        }
