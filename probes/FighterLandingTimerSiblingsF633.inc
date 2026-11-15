// F633 genuine sibling original native action0x97/98/9A: timed float progress, x87
// ground correction, contact rebound and optional extra stage-zero
// projectile counter. Entire giant fighter Advance() is NONEXACT.
case F633_CASE: {
    field368=(field368)+g_AnimationDeltaAt0065747C;
    if ((field368)>g_AnimationMaximumAt006583B4)
        field368=1000.0f;
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
#if F633_EXTRA_FLAG && F633_EXTRA_BEFORE
        // 0058AF60 alone clears this genuine extra flag BEFORE the
        // trajectory short; 00543210 clears it AFTER motion init.
        reinterpret_cast<signed short&>(fieldF0A)=0;
#endif
        I16(F633_COUNTER)=0;
        velocityX=F633_START_HEIGHT;
        velocityY=0.0f;
        field07C=0;
#if F633_EXTRA_FLAG && !F633_EXTRA_BEFORE
        reinterpret_cast<signed short&>(fieldF0A)=0;
#endif
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_JumpGroundCorrectionAt00658058;
        if ((velocityX)>g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (ContactAt454EE0() && field3BE)
        field490=(velocityX)*g_JumpReflectionAt006583E8;
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(F633_NEXT_ACTION);
    break;
}
