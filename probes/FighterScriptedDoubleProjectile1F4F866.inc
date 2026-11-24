// F866 actual original 1F4 full 448B/136-x86/14 original PE fields.
// Genuine native narrow fourth argument at 00453C80 makes MOV r8, not MOVSX r32.
// Two physical stage4 projectile conditions; original whole giant still nonexact.
case 0x1F4: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::ThreeTenths;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero) {
            ClearMotionFields();
            ResetSecondaryCounter(0xD);
            y=0.0f;
            return;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0)
        SpawnBattleEffect(0x338,x,y,
            (facing),1);
    if ((animationStage)==4 && (animationFrame)==0) {
        PlaySound(1);
        velocityX=8.0f;
        velocityY=9.5f;
        field05C=0.65f;
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    if ((animationStage)==0xD && (animationFrame)==0)
        ResetSecondaryCounter(0xB);
    return;
}
