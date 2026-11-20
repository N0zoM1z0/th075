// F880 real original action 0x255, complete native interior.
// Native action9, float Y sprite37, Prepare21; stage8 aux6 only 255/257.
// Entire original fighter remains nonexact; this is no independent leaf.
case 0x255: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
        PlaySharedSound(0x21);
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    return;
}
