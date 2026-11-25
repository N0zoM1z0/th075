// F988 authentic Japanese fighter 004AC040 actions255/256/257.
 // Original complete internal handlers 258B/75, 176B/52,
 // 248B/72 x86; 7+5+6 native typed PE external target fields.
 // Natural normal VC7.1 source matches all opcode mnemonics/widths
 // but GPR/EBP saved-this owner still differs: 46/32/46 GPR roles.
 // Stage5 rawX/floatY 0x37, original 255 alone prepares action21;
 // original 255/257 alone perform stage8 auxiliary action6.
 // Entire 82KB giant is NONEXACT; do not credit cropped cases.
// F988 real Japanese original 004AC040 action 0x255
case 0x255: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
                remainingHits=1;
        collisionResult=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
        PlaySharedSound(0x21);
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    break;
}
// F988 real Japanese original 004AC040 action 0x256
case 0x256: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
                remainingHits=1;
        collisionResult=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
    }
    break;
}
// F988 real Japanese original 004AC040 action 0x257
case 0x257: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
                remainingHits=1;
        collisionResult=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    break;
}
