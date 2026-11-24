// F1004 original Japanese TH075 004AC040 native state2E5.
 // Complete original 004BD017..004BD314 765B/199x86, 14
 // actual typed PE targets. Mode signed BYTE 006714D0,
 // F02*5 two real 0x387 shots with native FILD/FSUBR X,
 // different Y global 0065836C, signed F06 cadence, F08
 // mode budget, randomized native 516 and late phase13 retry.
 // All 199 original mnemonic/width/GPR roles naturally match
 // in incomplete 82KB parent. Parent original EBP/frame
 // still not native: entire callable NONEXACT.
// F1004 original Japanese 004AC040 2E5 native dual projectile cadence
case 0x2E5: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        fieldF06=0;
        fieldF08=g_OptionsModeAt006714D0+2;
    }
    if ((animationStage)>4 && (animationStage)<11 && (fieldF08)>0) {
        --fieldF06;
        if ((fieldF06)>3-g_OptionsModeAt006714D0) {
            field314=float((scriptCounterF02)*5);
            SpawnBattleEffect(0x387,
                x -
                    float((facing)*16),
                (*(&y))+g_F972_YAt0065836C,
                facing,1);
            field314=float((scriptCounterF02)*5+180);
            SpawnBattleEffect(0x387,
                x -
                    float((facing)*16),
                (*(&y))+g_F972_YAt0065836C,
                facing,1);
            ++scriptCounterF02;
        }
        if ((fieldF06)<=0 && (fieldF06)<-30) {
            fieldF06=10;
            --fieldF08;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(
            RecordedRange(60,120)-g_OptionsModeAt006714D0*20);
    }
    if ((animationStage)==4 && (animationFrame)==0)
        fieldF06=10;
    if ((animationStage)==5 && (animationFrame)==0)
        PlaySound(5);
    if ((animationStage)==11 && (animationFrame)==0 && (fieldF08)>0)
        ResetSecondaryCounter(9);
    if ((animationStage)==13 && (animationFrame)==0) {
        ++fieldF04;
        if ((fieldF04)<13)
            ResetSecondaryCounter(11);
    }
    break;
}
