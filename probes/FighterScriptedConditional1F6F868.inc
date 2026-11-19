// F868 actual original 1F6: 372B/111-x86/12 real typed PE fields.
// Special U8 this+511 equals20, stage 8..10 triggers native 455B30 and exits.
// Stage5 float X/bitwise Y sprite80 and second sprite336, Prepare2.
// Full original enclosing fighter NONEXACT; no split-case CODE credit.
case 0x1F6: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_SubtractAt00657478;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if ((animationStage)>7 && (animationStage)<0xB && (aiCommand)==0x14) {
        ResetPrimaryCounters(0x1F7);
        ClearMotionFields();
        NativeGameEffectAt455B30();
        return;
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=14.0f;
        SpawnAuxEffect(0x80,
            float((facing)*100)+(x),
            y,(facing),1);
        SpawnBattleEffect(0x336,x,y,
            (facing),1);
        PlaySound(2);
    }
    return;
}
