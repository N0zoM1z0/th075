// F641: genuine original 71-instruction A3/A4/A5 timed landing
// actions with NO trajectory counter reset, unlike the earlier F633
// 73/75-x86 family. This is an inner case of a nonexact giant.
case F641_CASE: {
    F32(0x368)=F32(0x368)+g_AnimationDeltaAt0065747C;
    if (F32(0x368)>g_AnimationMaximumAt006583B4)
        F32(0x368)=1000.0f;
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS=F641_START_HEIGHT;
        POS54=0.0f;
        I32(0x7C)=0;
    }
    if (POS<g_ThresholdAt0065782C) {
        POS=POS+g_JumpGroundCorrectionAt00658058;
        if (POS>g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (ContactAt454EE0() && *reinterpret_cast<signed char*>(RAW+0x3BE))
        F32(0x490)=POS*g_JumpReflectionAt006583E8;
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetNativeActionAt40FAC0(F641_NEXT_ACTION);
    break;
}
