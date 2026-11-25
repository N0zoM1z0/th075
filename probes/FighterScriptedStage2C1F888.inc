// F888 real original game 0x2C1 stage1, true real 453B50 sprite345.
// F10=420 guard is stage>10 for 2C0 but ONLY getter match for 2C1.
// Full 46755B giant NONEXACT, do not treat original inner case as callable CODE.
case 0x2C1: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        collisionResult=0;
        remainingHits=1;
        ClearMotionFields();
    }
    if ((animationStage)==1 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        PlaySound(9);
        spellPower=(spellPower)-GeometryConstants::Hundred;
        SpawnAuxEffect(0x74,x,
            (*(&y))+GeometryConstants::Hundred,
            (facing),1);
    }

    if (AdvanceNestedFrame()==(animationStageCount)) {
        fieldF10=0x1A4;
        ResetPrimaryCounters(0);
        Fighter::SpawnTrackedEffect(0x345,x,
        (*(&y))+GeometryConstants::Hundred,1,1,0,1);
    }
    return;
}
