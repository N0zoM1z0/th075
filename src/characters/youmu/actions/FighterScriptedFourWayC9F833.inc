// F833: physical original 005214B0 case C9, 279 native CODE B, 86 x86.
// Real x87 signed-direction projectile coordinates, borrowed true x
// member at this+0x44, and native epilogue direct return.
// This is an ORIGINAL INTERIOR only, NOT an independent exact function.
case 0xC9: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=-15.0f;
        SpawnAuxEffect(0x7D,
            x-float((facing)*80),
            (*(&y))+GeometryConstants::Eighty,
            -(facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Eighty,
            -(facing),1);
        PlaySharedSound(31);
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::One;
        if ((velocityX)>FloatConstants::Zero) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    return;
}
