// F869 actual native game 1F7: 307B/90x86/11 physical original PE fields.
// Real stage4..6 U8+511 guard =>1F8 effect455B30; stage3 sprite337 Prepare3.
// True original function is whole fighter parent; no case exact CODE credit.
case 0x1F7: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::Half;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if ((animationStage)>3 && (animationStage)<7 && (aiCommand)==0x14) {
        ResetPrimaryCounters(0x1F8);
        ClearMotionFields();
        NativeGameEffectAt455B30();
        return;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        SpawnBattleEffect(0x337,x,y,
            (facing),1);
        PlaySound(3);
    }
    return;
}
