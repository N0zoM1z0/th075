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
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(velocityY)*g_BounceScaleAt00657F74;
        PlaySharedSound(0x2C);
#endif
        SpawnWithFloatAt453A70(F652_SPRITE,reinterpret_cast<int&>(x),
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
            SetAuxActionAt40FB40(2);
        else
            ResetPrimaryCounters(9);
    }
    break;
}
