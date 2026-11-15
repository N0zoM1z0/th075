// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
case F628_CASE: {
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
        velocityX=F628_START_POS;
        velocityY=0.0f;
        field07C=0;
        I16(F628_COUNTER)=0;
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_JumpGroundCorrectionAt00658058;
        if ((velocityX)>g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (ContactAt454EE0() && field3BE)
        field490=(velocityX)*g_JumpReflectionAt006583E8;
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    if (reinterpret_cast<signed short&>(animationStage)==3 && reinterpret_cast<signed short&>(animationFrame)==0 && I16(F628_COUNTER)<F628_LIMIT) {
        ++I16(F628_COUNTER);
        SetAuxActionAt40FB40(1);
    }
    break;
}
