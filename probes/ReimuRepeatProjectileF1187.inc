// Native 198/19E siblings of the earlier 192 projectile policy.
case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(2);
    if ((animationStage)==3 && (animationFrame)==0) {
        field314=40.0f; field318=10.0f;
        SpawnFloatXYAt453A70(R1187_EFFECT,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ThresholdAt0065782C,reinterpret_cast<char&>(facing),0);
        PlaySound(4);
        UpdateGaugeTimer(250);
    }
    if ((animationStage)==6 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(4);
    }
    break;
}
