// F1001 native original Japanese TH075 004AC040 actual 2BC/2BD.
 // 2BC 755B/199x86, 2BD 742B/196x86, 15 genuine PE fields
 // each. Correct stage3 original sprite0x73/0x74, real
 // 00453E80(0x28), action0x17, FILD/FSUBR signed facing
 // and actual initial Y PE global00659284, later pair Y0065836C. Stage4..10 2x 0x323/0x32B shots
 // with limit36/72; native 2BD writes short F14=1 while
 // 2BC updates F04. Native stage5 prep5/6; stage11 aux9.
 // Entire PARTIAL father produces all original mnemonics,
 // 2BC widths fully align, 2BD one original ADD width at
 // local ordinal133 remains nonnative, GPR roles differ.
// F1001 original SHA-pinned Japanese 004AC040 action 0x2BC
case 0x2BC: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=1;
        ClearMotionFields();
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        fieldF06=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        spellPower=(spellPower)-GeometryConstants::Hundred;
        SpawnAuxEffect(0x73,
            x
                - float((facing)*18),
            (*(&y))+g_EffectOffsetNinetyTwo,
            facing,1);
    }
    if ((fieldF04)>0)
        --fieldF04;
    if ((animationStage)>4 && (animationStage)<11 && (fieldF04)==0 && (scriptCounterF02)<36) {
        UpdateGaugeTimer(0xA);
        field314=float((scriptCounterF02)*5);
        SpawnBattleEffect(0x323,
            x
                - float((facing)*16),
            (*(&y))+GeometryConstants::HundredThirtySix,
            facing,1);
        field314=float((scriptCounterF02)*5+180);
        SpawnBattleEffect(0x323,
            x
                - float((facing)*16),
            (*(&y))+GeometryConstants::HundredThirtySix,
            facing,1);
        ++scriptCounterF02;
        ++fieldF04;
    }
    if ((animationStage)==5 && (animationFrame)==0)
        PlaySound(5);
    if ((animationStage)==11 && (animationFrame)==0 && (fieldF06)<5) {
        ResetSecondaryCounter(9);
        ++fieldF06;
    }
    break;
}
// F1001 original SHA-pinned Japanese 004AC040 action 0x2BD
case 0x2BD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=1;
        ClearMotionFields();
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        fieldF06=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        spellPower=(spellPower)-GeometryConstants::Hundred;
        SpawnAuxEffect(0x74,
            x
                - float((facing)*18),
            (*(&y))+g_EffectOffsetNinetyTwo,
            facing,1);
    }
    if ((fieldF04)>0)
        --fieldF04;
    if ((animationStage)>4 && (animationStage)<11 && (fieldF04)==0 && (scriptCounterF02)<72) {
        fieldF14=1;
        UpdateGaugeTimer(0xA);
        field314=float((scriptCounterF02)*5);
        SpawnBattleEffect(0x32B,
            x
                - float((facing)*16),
            (*(&y))+GeometryConstants::HundredThirtySix,
            facing,1);
        field314=float((scriptCounterF02)*5+180);
        SpawnBattleEffect(0x32B,
            x
                - float((facing)*16),
            (*(&y))+GeometryConstants::HundredThirtySix,
            facing,1);
        ++scriptCounterF02;
    }
    if ((animationStage)==5 && (animationFrame)==0)
        PlaySound(6);
    if ((animationStage)==11 && (animationFrame)==0 && (fieldF06)<5) {
        ResetSecondaryCounter(9);
        ++fieldF06;
    }
    break;
}
