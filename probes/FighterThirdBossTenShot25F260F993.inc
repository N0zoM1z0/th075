// F993 native Japanese original TH075 004AC040 25F and 260.
 // Both real original handlers 466B/114 x86, nine genuine PE
 // external fields per case. Source ten-iteration int loop
 // with native 30-shot*6 angle, sprite 0x346 vs 0x347,
 // signed facing*49 and float Y global00659294.
 // ENTIRE PARTIAL father source naturally reproduces ALL 228
 // original positional mnemonics, widths AND GPR roles.
 // Original saved-this EBP−0x64 and full 0x720 stack
 // frame still differ; no complete original callable exactness.
// F993 original Japanese fighter 004AC040 action 0x25F 10-shot loop.
case 0x25F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        collisionResult=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0 && (scriptCounterF00)<=0 && (scriptCounterF02)<1) {
        PlaySound(0);
        UpdateGaugeTimer(0x96);
        for (int shot=0;shot<10;++shot) {
            field314=float(30-shot*6);
            field318=15.0f;
            SpawnBattleEffect(0x346,
                float((facing)*49)+(x),
                (*(&y))+GeometryConstants::HundredSixteen,
                facing,1);
        }
        velocityX=float(scriptCounterF00)*FloatConstants::OneHundredth;
        velocityY=float(scriptCounterF02)*FloatConstants::OneHundredth;
        scriptCounterF00=2;
        ++scriptCounterF02;
    }
    break;
}
// F993 original Japanese fighter 004AC040 action 0x260 10-shot loop.
case 0x260: {
    if ((animationStage)==0 && (animationFrame)==0) {
        collisionResult=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0 && (scriptCounterF00)<=0 && (scriptCounterF02)<1) {
        PlaySound(0);
        UpdateGaugeTimer(0x96);
        for (int shot=0;shot<10;++shot) {
            field314=float(30-shot*6);
            field318=15.0f;
            SpawnBattleEffect(0x347,
                float((facing)*49)+(x),
                (*(&y))+GeometryConstants::HundredSixteen,
                facing,1);
        }
        velocityX=float(scriptCounterF00)*FloatConstants::OneHundredth;
        velocityY=float(scriptCounterF02)*FloatConstants::OneHundredth;
        scriptCounterF00=2;
        ++scriptCounterF02;
    }
    break;
}
