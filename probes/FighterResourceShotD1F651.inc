// F651 actual native D1 resource-gated movement and projectile shot.
// Source fragment belongs inside still-NONEXACT giant fighter Advance().
case 0xD1: {
    if (spirit<2) {
        SetNativeActionAt40FAC0(0);
        break;
    }
    spirit=spirit-F651_DECAY;
    if (animationStage==0 && animationFrame==0) {
        ResetAt453E20();
        PrepareActionAt453D60(0x2C);
        SpawnWithFloatAt453A70(F651_SPRITE,reinterpret_cast<int&>(x),
                (y)+g_ContactProjectionAt00657888,
                facing,1);
    }
    if (GetNativeActionAt40FA30()==field070) {
        if (static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0)
            SetAuxActionAt40FB40(2);
        else
            SetNativeActionAt40FAC0(0);
    }
    break;
}
