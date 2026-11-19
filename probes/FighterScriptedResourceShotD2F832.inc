// F832 original 005214B0 native D2 interior case (251 B/74 x86).
// Real x87 speed scale happens BEFORE projectile, real decay 6.
// F652 native complete D2 resource shot with real x87 speed scaling.
// Not a whole-function source match; this is an internal case.
case 0xD2: {
    if (spirit<2) {
        ResetPrimaryCounters(9);
        return;
    }
    spirit=spirit-F652_DECAY;
    if (animationStage==0 && animationFrame==0) {
#if F652_SCALE_BEFORE
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(velocityY)*g_BounceScaleAt00657F74;
        PlaySharedSound(0x2C);
#endif
        SpawnBattleEffect(F652_SPRITE,x,
                (y)+g_ContactProjectionAt00657888,
                facing,1);
#if !F652_SCALE_BEFORE
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(velocityY)*g_BounceScaleAt00657F74;
        PlaySharedSound(0x2C);
#endif
    }
    // The original applies this x87 drag every frame, even outside
    // the stage/frame-zero projectile initialization path.
    velocityY=velocityY-(field05C)*g_BounceScaleAt00657F74;
    if (AdvanceNestedFrame()==field070) {
        if (static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0)
            ResetSecondaryCounter(2);
        else
            ResetPrimaryCounters(9);
    }
    return;
}
