// F652 native complete D2 resource shot with real x87 speed scaling.
// Not a whole-function source match; this is an internal case.
case 0xD2: {
    if (reinterpret_cast<signed short&>(meter)<2) {
        SetNativeActionAt40FAC0(9);
        break;
    }
    reinterpret_cast<signed short&>(meter)=reinterpret_cast<signed short&>(meter)-F652_DECAY;
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
#if F652_SCALE_BEFORE
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(velocityY)*g_BounceScaleAt00657F74;
        PrepareActionAt453D60(0x2C);
#endif
        SpawnWithFloatAt453A70(F652_SPRITE,reinterpret_cast<int&>(x),
                (y)+g_ContactProjectionAt00657888,
                facing,1);
#if !F652_SCALE_BEFORE
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(velocityY)*g_BounceScaleAt00657F74;
        PrepareActionAt453D60(0x2C);
#endif
    }
    // The original applies this x87 drag every frame, even outside
    // the stage/frame-zero projectile initialization path.
    velocityY=velocityY-(field05C)*g_BounceScaleAt00657F74;
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070)) {
        if (static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0)
            SetAuxActionAt40FB40(2);
        else
            SetNativeActionAt40FAC0(9);
    }
    break;
}
