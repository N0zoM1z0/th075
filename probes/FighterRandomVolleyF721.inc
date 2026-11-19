// F721: original complete native action 2E5 (0054F241..0054F55F):
// 798 original CODE B /223 x86. Genuine seven-argument projectile,
// original random direction/facing and stage-count based shots.
// Native original whole giant remains NONEXACT; no individual case credit.
        case 0x2E5: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                scriptCounterF00=0;
                scriptCounterF02=0;
                field07C=1;
                ClearMotionFields();
                Fighter::SpawnTrackedEffect(0x38E,x,y,
                    facing,1,0,1);
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                aiCardTimer=static_cast<short>(RecordedRange(60,80)
                   -static_cast<int>(g_CloudOpponentAt006714D0)*20);
            }
            if ((animationStage)==3 && (animationFrame)==0)
                PlaySound(9);
            if ((animationStage)==7 && (animationFrame)==0) {
                if (opponent->y==g_ThresholdAt0065782C)
                    scriptCounterF00=0;
                else
                    scriptCounterF00=20;
                if (RecordedRange(0,100)<20) {
                    if (RecordedRange(0,100)<50)
                        scriptCounterF00=0;
                    else
                        scriptCounterF00=20;
                }
                field314=scriptCounterF00;
                SpawnBattleEffect(0x386,
                    float(facing*65)+(x),
                    (*(&y))+g_BarrageY1At006591EC,
                    facing,1);
            }
            if ((animationStage)==10 && (animationFrame)==0
                && (scriptCounterF02)<(3-static_cast<int>(g_CloudOpponentAt006714D0))*2) {
                ++scriptCounterF02;
                ResetSecondaryCounter(9);
            }
            if ((animationStage)==12 && (animationFrame)==0) {
                field314=scriptCounterF00;
                if ((scriptCounterF00)==0)
                    SpawnBattleEffect(0x384,
                        float(facing*65)+(x),
                        (*(&y))+g_BarrageY1At006591EC,
                        facing,1);
                if ((scriptCounterF00)==20)
                    SpawnBattleEffect(0x388,
                        float(facing*65)+(x),
                        (*(&y))+g_BarrageY1At006591EC,
                        facing,1);
                PlaySound(10);
            }
            break;
        }
