// F969 original Japanese TH075 fighter 004AC040 true state 0x192.
 // Native 004B2611..004B28ED, 732B/177x86/11 real external PE fields.
 // C++ naturally emits ALL 177 matching mnemonics and original widths:
 // three FLOAT X=FILD(count-dependent facing product)+member X, three
 // FLOAT Y=member Y+original-global+integer FIADD(count*20), and
 // three frame/angle FILD values. Real temp stack slots remain
 // nonnative EBP-0x84..-0xA4 instead of actual -0xD8..-0xF8;
 // 121 true native GPR-role mismatches still prevent whole exactness.
 // Original 82KB father still incomplete, no independent case credit.
// F969 genuine original Japanese 004AC040 0x192 stage3 three-shot trial.
case 0x192: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>4 && (scriptCounterF00)<=0 && (scriptCounterF02)<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float((scriptCounterF02)*4+45);
        field318=7.0f;
        SpawnBattleEffect(0x320,
          float((47-(scriptCounterF02)*10)*(facing))+(x),
          (*(&y))+GeometryConstants::Sixty+(scriptCounterF02)*20,
          facing,1);
        field314=float((scriptCounterF02)*4+49);
        field318=7.0f;
        SpawnBattleEffect(0x320,
          float((47-(scriptCounterF02)*10)*(facing))+(x),
          (*(&y))+GeometryConstants::Sixty+(scriptCounterF02)*20,
          facing,1);
        field314=float((scriptCounterF02)*4+41);
        field318=7.0f;
        SpawnBattleEffect(0x320,
          float((47-(scriptCounterF02)*10)*(facing))+(x),
          (*(&y))+GeometryConstants::Sixty+(scriptCounterF02)*20,
          facing,1);
        scriptCounterF00=2;
        ++scriptCounterF02;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(2);
    break;
}
