// F867 original native 1F5 628B/195x86/17 physically correct PE fields.
// Original stage1/2/13/14/15/24 separate checks, native char fourth parameter.
// Native lower height comparator global 657480, not apparent equivalent 65782C.
// Full enclosing fighter still GPR and final JMP nonexact.
case 0x1F5: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
        field3AC=0;
    }
    if ((velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::ThreeTenths;
        if ((velocityX)<FloatConstants::Two)
            velocityX=2.0f;
    }
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-verticalAcceleration;
        if (y+velocityY<=FloatConstants::Zero) {
            ClearMotionFields();
            ResetSecondaryCounter(0x18);
            y=0.0f;
            return;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==1 && (animationFrame)==0) {
        velocityX=9.5f;
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        SpawnBattleEffect(0x33B,x,y,
            (facing),1);
        PlaySound(1);
    }
    if ((animationStage)==0xD && (animationFrame)==0) {
        SpawnBattleEffect(0x338,x,y,
            (facing),1);
        PlaySound(1);
    }
    if ((animationStage)==0xE && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
    }
    if ((animationStage)==0xF && (animationFrame)==0) {
        velocityX=10.0f;
        velocityY=15.0f;
        verticalAcceleration=0.65f;
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    if ((animationStage)==0x18 && (animationFrame)==0)
        ResetSecondaryCounter(0x16);
    return;
}
