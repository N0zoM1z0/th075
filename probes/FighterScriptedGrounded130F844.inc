// F844 original selected 005214B0 native stage0x130 202B/58 x86.
// Native x87 position/grounded drag and two entire-parent returns.
// Physical PE shows prepare stage3, animation1C, action9.
// Not independently callable whole original game CODE.
case 0x130: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(0xA);
        y=0.0f;
        field05C=0.0f;
        velocityY=0.0f;
        return;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==3 && (animationFrame)==0)
        PlaySharedSound(0x1C);
    return;
}
