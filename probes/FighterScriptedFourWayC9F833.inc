// F833: physical original 005214B0 case C9, 279 native CODE B, 86 x86.
// Real x87 signed-direction projectile coordinates, borrowed true x
// member at this+0x44, and native epilogue direct return.
// This is an ORIGINAL INTERIOR only, NOT an independent exact function.
case 0xC9: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=-15.0f;
        SpawnAt453C80(0x7D,
            x-float((facing)*80),
            (*(&y))+g_F701_VolleyYAt00658268,
            -(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_F701_VolleyYAt00658268,
            -(facing),1);
        PlaySharedSound(31);
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_AnimationDeltaAt0065747C;
        if ((velocityX)>g_ThresholdAt0065782C) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    return;
}
