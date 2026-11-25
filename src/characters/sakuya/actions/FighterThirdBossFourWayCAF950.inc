// F950: independently reconstructed native Japanese TH075 004AC040
// original action0xCA, 004B04CC..004B0680 436 CODE B /123 x86.
// The ordinary C++ emits 430B/123 original x86 with ALL native
// mnemonic and GPR-role positions equal, but two native wide EBP−0x98
// integer-to-x87 spill instructions are short because the still
// PARTIAL 82KB original father uses only a 0x40 stack frame.
// The original game giant remains NONEXACT; no case-only credit.
case 0xCA: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        verticalAcceleration=0.0f;
        scriptCounterF00=0;
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=11.0f;
        velocityY=5.0f;
        verticalAcceleration=0.6f;
        SpawnAuxEffect(0x7D,
            float((facing)*80)+(x),
            (*(&y))+GeometryConstants::Seventy,
            facing,1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Seventy,
            facing,1);
        PlaySharedSound(31);
    }
    if (y>FloatConstants::Zero && (animationStage)>1) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f;
            velocityY=0.0f;
            verticalAcceleration=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    else if (animationStage < animationStageCount) {
        // Continue the current animation.
    }
    break;
}
