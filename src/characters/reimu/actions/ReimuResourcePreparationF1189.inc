case R1189_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --bombCount;
        ClearMotionFields();
        remainingHits=1; collisionResult=0; field3AC=0; scriptCounterF00=0;
    }
#if R1189_HAS_BONUS
    if ((spiritCooldown)==0 && collisionResult==1) spirit=1000;
#endif
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,(*(&y))+GeometryConstants::Hundred,
            facing,1);
        PlaySharedSound(0x21);
        opponent->fieldEFA=0;
    }
    break;
}
