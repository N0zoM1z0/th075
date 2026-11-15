// F651 actual native D1 resource-gated movement and projectile shot.
// Source fragment belongs inside still-NONEXACT giant fighter Advance().
case 0xD1: {
    if (reinterpret_cast<signed short&>(meter)<2) {
        SetNativeActionAt40FAC0(0);
        break;
    }
    reinterpret_cast<signed short&>(meter)=reinterpret_cast<signed short&>(meter)-F651_DECAY;
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
        ResetAt453E20();
        PrepareActionAt453D60(0x2C);
        SpawnWithFloatAt453A70(F651_SPRITE,reinterpret_cast<int&>(x),
                (y)+g_ContactProjectionAt00657888,
                facing,1);
    }
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070)) {
        if (static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0)
            SetAuxActionAt40FB40(2);
        else
            SetNativeActionAt40FAC0(0);
    }
    break;
}
