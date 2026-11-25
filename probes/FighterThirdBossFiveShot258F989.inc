// Sakuya action 0x258 at 0x004B7BB0 fires five 0x325 shots with script-relative
// angles, then sets the gauge timer to 100.
case 0x258: {
    if ((animationStage)==0 && (animationFrame)==0) {
        collisionResult=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>4) {
        if ((scriptCounterF02)<3 && (scriptCounterF00)<=0) {
            PlaySound(0);
            field314=float((scriptCounterF02)*3+100);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                float((facing)*97)+(x),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+95);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                float((facing)*97)+(x),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+90);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                float((facing)*97)+(x),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+85);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                float((facing)*97)+(x),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+80);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                float((facing)*97)+(x),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            UpdateGaugeTimer(0x64);
            ++scriptCounterF02;
            scriptCounterF00=3;
        }
        --scriptCounterF00;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    break;
}
