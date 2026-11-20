// F856 selected actor original 190: 217B/64 x86/six native PE fields.
// Stage3 actual sprite320, animationFA, prepare0; stage4 state bit.
// Normal C++ whole original game interior, source GPR not exact.
case 0x190: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        field314=1.0f;
        SpawnBattleEffect(0x320,x,y,
           (facing),1);
        UpdateGaugeTimer(0xFA);
        PlaySound(0);
    }
    if ((animationStage)==4 && (animationFrame)==0)
        field07C=1;
    return;
}
