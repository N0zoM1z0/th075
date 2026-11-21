// F989 SHA-pinned Japanese original TH075 004AC040 action258:
 // physical 004B7BB0..004B7EF2, 834B/212 native x86, 15 real
 // original typed PE/COFF external fields. Five genuine separate
 // 0x325 shots with F02*3+100/95/90/85/80 and signed facing*97,
 // true Y global00659498, followed by animation0x64 and real
 // signed-short counters. Full-partial father source mnemonics and
 // instruction widths align, but 137 GPR roles still wrong.
 // Original 82KB whole game father remains NONEXACT.
// F989 original Japanese TH075 fighter 004AC040 action258
case 0x258: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
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
