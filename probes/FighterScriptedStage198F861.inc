// F861 physically bounded native 198: 199B/60 x86/7 PE fields.
// True actor state2 and stage4, sprite351, signed facing*90 and Y global659460.
// Complete original game interior, giant original still nonexact.
case 0x198: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(2);
    if ((animationStage)==4 && (animationFrame)==0) {
        PlaySound(3);
        SpawnBattleEffect(0x351,
            float((facing)*90)+(x),
            (*(&y))+g_F861ShotYAt00659460,
            (facing),1);
        UpdateGaugeTimer(0xC8);
    }
    return;
}
