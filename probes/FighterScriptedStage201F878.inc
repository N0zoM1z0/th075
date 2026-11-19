// F878 native 201 full 267B/80 x86/8 true original PE fields.
// Stage5 contains TWO separate guards: sprite336, Prepare2, then POS30.
// Native 65782C threshold and 658350 drop are both physical PE evidence.
case 0x201: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_F873GroundDropAt00658350;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnBattleEffect(0x336,x,y,
            (facing),1);
        PlaySound(2);
    }
    if ((animationStage)==5 && (animationFrame)==0)
        velocityX=30.0f;
    return;
}
