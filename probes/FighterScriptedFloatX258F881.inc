// F881 original native action258 206B/60 x86/6 genuine physical PE fields.
// Stage2 sprite340 float X from FILD signed facing*80, original raw integer Y.
// Native narrow char parameter, StartAnimation46D000(FA), Prepare5.
// Enclosing full fighter NONEXACT; no separate callable case credit.
case 0x258: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=1;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        Fighter::SpawnBattleEffect(0x340,
            float((facing)*80)+(x),
            y,(facing),1);
        UpdateGaugeTimer(0xFA);
        PlaySound(5);
    }
    return;
}
