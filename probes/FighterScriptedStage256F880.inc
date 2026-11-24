// F880 real original action 0x256, complete native interior.
// Native action9, float Y sprite37, Prepare21; stage8 aux6 only 255/257.
// Entire original fighter remains nonexact; this is no independent leaf.
case 0x256: {
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
            (*(&y))+GeometryConstants::Hundred,
            (facing),1);
        PlaySharedSound(0x21);
    }

    return;
}
