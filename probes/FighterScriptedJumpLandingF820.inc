// F820 native selected scripted giant action8C/8F/90,
 // each whole original inner case 289B/80 x86 with 8 PE fields.
 // Original final JMP goes directly to complete enclosing
 // 005214B0 epilogue; this void Advance naturally returns.
 // Source-only native view, not independent exact game functions.
// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
case F628_CASE: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=F628_START_POS;
        velocityY=0.0f;
        field07C=0;
        scriptCounterF00=0;
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::ThreeFifths;
        if ((velocityX)>FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        field490=(velocityX)*FloatConstants::ThreeQuartersDouble;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(0);
    if (animationStage==3 && animationFrame==0 && scriptCounterF00<F628_LIMIT) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    return;
}
