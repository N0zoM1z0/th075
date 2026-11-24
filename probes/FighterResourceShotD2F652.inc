// F652 native complete D2 resource shot with real x87 speed scaling.
// Not a whole-function source match; this is an internal case.
case 0xD2: {
    if (spirit<2) {
        ResetPrimaryCounters(9);
        break;
    }
    spirit=spirit-F652_DECAY;
    if (animationStage==0 && animationFrame==0) {
#if F652_SCALE_BEFORE
        velocityX=(velocityX)*FloatConstants::Quarter;
        velocityY=(velocityY)*FloatConstants::Quarter;
        PlaySharedSound(0x2C);
#endif
        SpawnBattleEffect(F652_SPRITE,x,
                (y)+g_ContactProjectionAt00657888,
                facing,1);
#if !F652_SCALE_BEFORE
        velocityX=(velocityX)*FloatConstants::Quarter;
        velocityY=(velocityY)*FloatConstants::Quarter;
        PlaySharedSound(0x2C);
#endif
    }
    // The original applies this x87 drag every frame, even outside
    // the stage/frame-zero projectile initialization path.
    velocityY=velocityY-(field05C)*FloatConstants::Quarter;
    if (AdvanceNestedFrame()==animationStageCount) {
        if (static_cast<unsigned int>(inputD)>0)
            ResetSecondaryCounter(2);
        else
            ResetPrimaryCounters(9);
    }
    break;
}
