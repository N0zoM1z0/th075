// F651 actual native D1 resource-gated movement and projectile shot.
// Source fragment belongs inside still-NONEXACT giant fighter Advance().
case 0xD1: {
    if (spirit<2) {
        ResetPrimaryCounters(0);
        break;
    }
    spirit=spirit-F651_DECAY;
    if (animationStage==0 && animationFrame==0) {
        ClearMotionFields();
        PlaySharedSound(0x2C);
        SpawnBattleEffect(F651_SPRITE,x,
                (y)+GeometryConstants::Hundred,
                facing,1);
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        if (static_cast<unsigned int>(inputD)>0)
            ResetSecondaryCounter(2);
        else
            ResetPrimaryCounters(0);
    }
    break;
}
