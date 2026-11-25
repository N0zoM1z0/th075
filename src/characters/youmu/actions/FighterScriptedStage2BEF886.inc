// F886 actual original native 2BE 461B/136 x86/15 physical PE fields.
// Two true F32-to-short casts generate native __ftol2 original PE call 6406AC.
// Sprite33C needs actual RAW integer Y: floating formal adds nonnative FILD/FSTP.
// Whole original game fighter NONEXACT; no split-case acceptance.
case 0x2BE: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        collisionResult=0;
        remainingHits=6;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationFrame)==0)
        collisionResult=0;
    if ((animationStage)==2 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        spellPower=(spellPower)-GeometryConstants::Hundred;
        SpawnAuxEffect(0x73,
            x-
                float((facing)*64),
            (*(&y))+GeometryConstants::SeventySeven,
            (facing),1);
        scriptCounterF00=(x);
        scriptCounterF02=(y);
        Fighter::SpawnTrackedEffect(0x33C,x,y,
            (facing),1,0,1);
    }
    if ((animationStage)==10 && (animationFrame)==0) {
        UpdateGaugeTimer(0x1F4);
        PlaySound(6);
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        SetCameraShake(5.0f);
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    return;
}
