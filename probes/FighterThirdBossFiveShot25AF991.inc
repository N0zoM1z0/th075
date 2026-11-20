// F991 actual original Japanese TH075 004AC040 action25A.
 // Original game PE 004B823F..004B84BA 635B/166 x86/15
 // typed external call/global fields. FIVE non-looping
 // sprite0x325 shots at angles 10/5/0/5/10, each native
 // facing*97 float X and original global00659498 Y.
 // Source all mnemonics/widths match in whole partial
 // parent; 97 real GPR roles remain wrong, giant NONEXACT.
// F991 pinned original Japanese 004AC040 action 25A native five-shot
case 0x25A: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(0);
        field314=10.0f;
        field318=10.0f;
        SpawnBattleEffect(0x325,
            float((facing)*97)+(x),
            (*(&y))+g_F971_YAt00659498,
            facing,1);
        field314=5.0f;
        field318=10.0f;
        SpawnBattleEffect(0x325,
            float((facing)*97)+(x),
            (*(&y))+g_F971_YAt00659498,
            facing,1);
        field314=0.0f;
        field318=10.0f;
        SpawnBattleEffect(0x325,
            float((facing)*97)+(x),
            (*(&y))+g_F971_YAt00659498,
            facing,1);
        field314=5.0f;
        field318=10.0f;
        SpawnBattleEffect(0x325,
            float((facing)*97)+(x),
            (*(&y))+g_F971_YAt00659498,
            facing,1);
        field314=10.0f;
        field318=10.0f;
        SpawnBattleEffect(0x325,
            float((facing)*97)+(x),
            (*(&y))+g_F971_YAt00659498,
            facing,1);
        UpdateGaugeTimer(0xFA);
    }
    break;
}
