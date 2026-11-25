// F859 current Japanese original 194 full interior 297B/86x86/7 physical fields.
// IMPORTANT: no stage0 ResetAt453E20 call, unlike sibling source 192.
// Actual ground motion/early stateA, stage5 2f sprite320, stage6 state flag.
// Current whole giant remains register/JMP NONEXACT.
case 0x194: {
    if ((animationStage)==0 && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
    }
    velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(0xA);
        y=0.0f;
        field05C=0.0f;
        velocityY=0.0f;
        return;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        field314=2.0f;
        SpawnBattleEffect(0x320,x,y,
           (facing),1);
        UpdateGaugeTimer(0xFA);
        PlaySound(0);
    }
    if ((animationStage)==6 && (animationFrame)==0)
        collisionResult=1;
    return;
}
