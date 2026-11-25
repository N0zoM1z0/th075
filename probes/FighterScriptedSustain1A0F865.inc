// F865 native original 1A0: 235B/67 x86/five real original PE fields.
// Meaningful float+54 lvalue needed for native FLD member/ FMUL global widths.
// Enclosing giant remains original GPR and full-parent-JMP nonexact.
case 0x1A0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
        velocityX=(velocityX)*FloatConstants::OneFifth;
        velocityY=(*(&velocityY))*FloatConstants::OneFifth;
    }
    if (y+velocityY<=FloatConstants::Zero) {
        velocityX=0.0f;
        velocityY=0.0f;
        y=0.0f;
    }
    if ((animationStage)>3)
        velocityY=velocityY-verticalAcceleration;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0)
        collisionResult=1;
    return;
}
