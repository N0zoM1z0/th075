// F855 native original 18B: 353B/99 x86/7 physical PE fields.
// Real prefix 16-bit ++, stage7 aux6 and stage6 facing*128 FILD.
// Incomplete giant register allocation remains nonnative; no case exact credit.
case 0x18B: {
    if ((animationStage)==0 && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
        velocityX=10.0f;
        scriptCounterF00=0;
    }
    if ((animationStage)>6) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(2);
    if ((animationStage)==7 && (animationFrame)==0 && (scriptCounterF00)<2) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
        remainingHits=1;
        collisionResult=0;
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        SpawnBattleEffect(0x328,
            float((facing)*128)+(x),
            (*(&y))+GeometryConstants::Seventy,
            (facing),1);
    }
    return;
}
