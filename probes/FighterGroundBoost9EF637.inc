// F637 natural original case0x9E: timed ground approach + launch.
// This is a case within a still NONEXACT huge fighter Advance(),
// not an accepted whole original function or ASM byte substitution.
case 0x9E: {
    F32(0x368)=F32(0x368)+g_AnimationDeltaAt0065747C;
    if (F32(0x368)>g_AnimationMaximumAt006583B4)
        F32(0x368)=1000.0f;
    if (I16(0x62)==0 && I16(0x64)==0) {
#if F637_EXTRA_FLAG && F637_EXTRA_BEFORE
        I16(0xF0A)=0;
#endif
        POS=-6.0f;
        POS54=8.0f;
        POS5C=0.75f;
#if F637_EXTRA_FLAG && !F637_EXTRA_BEFORE
        I16(0xF0A)=0;
#endif
    }
    // Original 005D73C0 uses a STRICT above-ground comparison:
    // native FCOMP/TEST AH,0x41/JNE. The other ten use >=, whose
    // genuine original TEST AH,1/JNE has different equality behavior.
#if F637_STRICT_ABOVE
    if (POS48>g_ThresholdAt0065782C) {
#else
    if (POS48>=g_ThresholdAt0065782C) {
#endif
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            POS48=0.0f;
            ResetAt453E20();
            break;
        }
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetNativeActionAt40FAC0(9);
    break;
}
