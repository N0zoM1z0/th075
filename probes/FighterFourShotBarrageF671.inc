// F671: native original 00543210 action 0x258 four-shot barrage C++.
// This entire original case has 134 authentic x86 and 12 true PE fields,
// but is deliberately NONSTRICT: four original EBP integer-to-float
// conversion scratch pairs -0x114..-0x120 compile at -0x2C..-0x38.
// This is not whole-giant or native-inner-case strict acceptance.
case 0x258: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                UpdateGaugeTimer(100);
                field314=-110.0f;
                field318=5.0f;
                SpawnBattleEffect(0x322,
                    float(facing*40)+(x),
                    (*(&y))+g_BarrageY1At006591EC,
                    facing,1);
                field314=110.0f;
                field318=5.0f;
                SpawnBattleEffect(0x322,
                    float(facing*40)+(x),
                    (*(&y))+g_BarrageY2At006581DC,
                    facing,1);
                field314=-70.0f;
                field318=4.0f;
                SpawnBattleEffect(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_BarrageY3At0065908C,
                    facing,1);
                field314=70.0f;
                field318=4.0f;
                SpawnBattleEffect(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            break;
        }
