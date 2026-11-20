// F642: original 97-x86 A7/A8 stage-zero projectile and time decay.
// Real floating from signed direction and signed short counter; this
// is a case INSIDE one currently NONEXACT fighter giant function.
case F642_CASE: {
    cardGauge=(cardGauge)+g_AnimationDeltaAt0065747C;
    if ((cardGauge)>g_AnimationMaximumAt006583B4)
        cardGauge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
        UpdateGaugeTimer(0xFA);
        PlaySharedSound(0x2C);
        scriptCounterF00=0xB4;
        SpawnAuxEffect(0x38,
            static_cast<float>(static_cast<int>(facing)*30)+(x),
            // VC7.1's real member y lvalue forces the native
            // FLD member / FADD global x87 order. y alias gives
            // the opposite physical operand sequence in this context.
            (y)+g_ContactProjectionAt00657888,
            facing,1);
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_JumpGroundCorrectionAt00658058;
        if ((velocityX)>g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    field490=(-scriptCounterF00)*g_ProjectileFallAt006590B4;
    if (scriptCounterF00>0)
        scriptCounterF00=scriptCounterF00-10;
    if (AdvanceNestedFrame()==field070)
        ResetPrimaryCounters(F642_NEXT_ACTION);
    break;
}
