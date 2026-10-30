// F822 selected original landings 97/98/9A, 276B/73 x86/9 fields each.
// F633 genuine sibling original native action0x97/98/9A: timed float progress, x87
// ground correction, contact rebound and optional extra stage-zero
// projectile counter. Entire giant fighter Advance() is NONEXACT.
case F633_CASE: {
    F32(0x368)=F32(0x368)+g_AnimationDeltaAt0065747C;
    if (F32(0x368)>g_AnimationMaximumAt006583B4)
        F32(0x368)=1000.0f;
    if (I16(0x62)==0 && I16(0x64)==0) {
#if F633_EXTRA_FLAG && F633_EXTRA_BEFORE
        // 0058AF60 alone clears this genuine extra flag BEFORE the
        // trajectory short; 00543210 clears it AFTER motion init.
        I16(0xF0A)=0;
#endif
        I16(F633_COUNTER)=0;
        POS=F633_START_HEIGHT;
        POS54=0.0f;
        I32(0x7C)=0;
#if F633_EXTRA_FLAG && !F633_EXTRA_BEFORE
        I16(0xF0A)=0;
#endif
    }
    if (POS<g_ThresholdAt0065782C) {
        POS=POS+g_JumpGroundCorrectionAt00658058;
        if (POS>g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (ContactAt454EE0() && *reinterpret_cast<signed char*>(RAW+0x3BE))
        F32(0x490)=POS*g_JumpReflectionAt006583E8;
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetNativeActionAt40FAC0(F633_NEXT_ACTION);
    return;
}
