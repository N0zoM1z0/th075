// Native 198/19E siblings of the earlier 192 projectile policy.
case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(2);
    if ((animationStage)==3 && (animationFrame)==0) {
        field314=40.0f; field318=10.0f;
        SpawnBattleEffect(R1187_EFFECT,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ThresholdAt0065782C,facing,0);
        PlaySound(4);
        UpdateGaugeTimer(250);
    }
    if ((animationStage)==6 && (animationFrame)==0 && (scriptCounterF00)<2) {
        ++scriptCounterF00;
        ResetSecondaryCounter(4);
    }
    break;
}
