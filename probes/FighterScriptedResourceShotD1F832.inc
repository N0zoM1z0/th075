// F832 original 005214B0 native D1 interior case (199 B/59 x86).
// Natural original source, real decay 6 and direct original parent exit.
// F651 actual native D1 resource-gated movement and projectile shot.
// Source fragment belongs inside still-NONEXACT giant fighter Advance().
case 0xD1: {
    if (spirit<2) {
        ResetPrimaryCounters(0);
        return;
    }
    spirit=spirit-F651_DECAY;
    if (animationStage==0 && animationFrame==0) {
        ClearMotionFields();
        PlaySharedSound(0x2C);
        SpawnBattleEffect(F651_SPRITE,x,
                (y)+g_ContactProjectionAt00657888,
                facing,1);
    }
    if (AdvanceNestedFrame()==field070) {
        if (static_cast<unsigned int>(reinterpret_cast<int&>(inputD))>0)
            ResetSecondaryCounter(2);
        else
            ResetPrimaryCounters(0);
    }
    return;
}
