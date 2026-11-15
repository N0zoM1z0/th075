// Native 198/19E siblings of the earlier 192 projectile policy.
case R1187_ACTION: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field314=40.0f; field318=10.0f;
        SpawnFloatXYAt453A70(R1187_EFFECT,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ThresholdAt0065782C,reinterpret_cast<char&>(facing),0);
        PlaySoundAt453D40(4);
        StartAnimationAt46D000(250);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(4);
    }
    break;
}
