// F862 physical original 19A 302B/86 x86/eight typed PE fields.
// No stage-zero/reset prefix: adding it makes an INVALID 332B/96x86
// function interior while deceptively making last 302B match GPRs.
// Real ground fall, sprite352 facing*60, stage5 motion, stage6 flag.
case 0x19A: {
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
        SpawnBattleEffect(0x352,
            float((facing)*60)+(x),
            (*(&y))+GeometryConstants::Eighty,
            (facing),1);
        UpdateGaugeTimer(0xC8);
        PlaySound(3);
        velocityX=-5.0f;
        velocityY=12.0f;
        field05C=0.65f;
    }
    if ((animationStage)==6 && (animationFrame)==0)
        field07C=1;
    return;
}
