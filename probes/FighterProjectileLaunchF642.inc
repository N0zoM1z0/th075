// F642: original 97-x86 A7/A8 stage-zero projectile and time decay.
// Real floating from signed direction and signed short counter; this
// is a case INSIDE one currently NONEXACT fighter giant function.
case F642_CASE: {
    F32(0x368)=F32(0x368)+g_AnimationDeltaAt0065747C;
    if (F32(0x368)>g_AnimationMaximumAt006583B4)
        F32(0x368)=1000.0f;
    if (I16(0x62)==0 && I16(0x64)==0) {
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D60(0x2C);
        I16(F642_COUNTER)=0xB4;
        SpawnAt453C80(0x38,
            static_cast<float>(static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66))*30)+F32(0x44),
            // VC7.1's real member F32(0x48) lvalue forces the native
            // FLD member / FADD global x87 order. POS48 alias gives
            // the opposite physical operand sequence in this context.
            F32(0x48)+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (POS<g_ThresholdAt0065782C) {
        POS=POS+g_JumpGroundCorrectionAt00658058;
        if (POS>g_ThresholdAt0065782C)
            POS=0.0f;
    }
    F32(0x490)=(-I16(F642_COUNTER))*g_ProjectileFallAt006590B4;
    if (I16(F642_COUNTER)>0)
        I16(F642_COUNTER)=I16(F642_COUNTER)-10;
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetNativeActionAt40FAC0(F642_NEXT_ACTION);
    break;
}
