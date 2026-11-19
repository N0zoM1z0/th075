case R1189_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
#if R1189_AIR
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
        field07C=1;
#else
        field07C=1;
        ClearMotionFields();
#endif
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(R1189_NEXT_ACTION);
    if ((animationStage)==R1189_FIRE_STAGE && (animationFrame)==0) {
        field314=0.0f;
        field318=(*(&y))+R1189_Y_OFFSET;
        SpawnBattleEffect(R1189_EFFECT,float(facing*R1189_X_OFFSET)+(x),
            (*(&y))+R1189_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        field314=1.0f;
        SpawnBattleEffect(R1189_EFFECT,float(facing*R1189_X_OFFSET)+(x),
            (*(&y))+R1189_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        field314=2.0f;
        SpawnBattleEffect(R1189_EFFECT,float(facing*R1189_X_OFFSET)+(x),
            (*(&y))+R1189_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        field314=3.0f;
        SpawnBattleEffect(R1189_EFFECT,float(facing*R1189_X_OFFSET)+(x),
            (*(&y))+R1189_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        UpdateGaugeTimer(250);
        PlaySound(4);
    }
    break;
}
