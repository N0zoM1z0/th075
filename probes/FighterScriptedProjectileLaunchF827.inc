// F827 actual original A7/A8 350B/97-x86/12PE fields each, real sprite 38 and 30x direction. Void whole-parent natural epilogue return. Not independently callable game CODE.
// F642: original 97-x86 A7/A8 stage-zero projectile and time decay.
// Real floating from signed direction and signed short counter; this
// is a case INSIDE one currently NONEXACT fighter giant function.
case F642_CASE: {
    cardGauge=(cardGauge)+FloatConstants::One;
    if ((cardGauge)>GeometryConstants::Thousand)
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
            (y)+GeometryConstants::Hundred,
            facing,1);
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::ThreeFifths;
        if ((velocityX)>FloatConstants::Zero)
            velocityX=0.0f;
    }
    field490=(-scriptCounterF00)*FloatConstants::OneTenth;
    if (scriptCounterF00>0)
        scriptCounterF00=scriptCounterF00-10;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(F642_NEXT_ACTION);
    return;
}
