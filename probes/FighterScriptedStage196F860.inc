// F860 native original game 196: 199B/60 x86/7 real PE call/global fields.
// Actual stage3 prepare3 -> sprite353 float XY -> animationC8.
// Natural float Y lvalue preserves native FLD member then FADD global.
// Whole original fighter nonexact; no split-case exact CODE.
case 0x196: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        PlaySound(3);
        SpawnBattleEffect(0x353,
            float((facing)*100)+(x),
            (*(&y))+g_F860ShotYAt006581DC,
            (facing),1);
        UpdateGaugeTimer(0xC8);
    }
    return;
}
