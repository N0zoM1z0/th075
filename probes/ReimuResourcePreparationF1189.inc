case R1189_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --field366;
        ClearMotionFields();
        field080=1; field07C=0; field3AC=0; scriptCounterF00=0;
    }
#if R1189_HAS_BONUS
    if ((spiritCooldown)==0 && field07C==1) spirit=1000;
#endif
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,(*(&y))+g_ContactProjectionAt00657888,
            facing,1);
        PlaySharedSound(0x21);
        opponent->fieldEFA=0;
    }
    break;
}
