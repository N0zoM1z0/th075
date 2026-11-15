// F642: original 97-x86 A7/A8 stage-zero projectile and time decay.
// Real floating from signed direction and signed short counter; this
// is a case INSIDE one currently NONEXACT fighter giant function.
case F642_CASE: {
    field368=(field368)+g_AnimationDeltaAt0065747C;
    if ((field368)>g_AnimationMaximumAt006583B4)
        field368=1000.0f;
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D60(0x2C);
        I16(F642_COUNTER)=0xB4;
        SpawnAt453C80(0x38,
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
    field490=(-I16(F642_COUNTER))*g_ProjectileFallAt006590B4;
    if (I16(F642_COUNTER)>0)
        I16(F642_COUNTER)=I16(F642_COUNTER)-10;
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(F642_NEXT_ACTION);
    break;
}
