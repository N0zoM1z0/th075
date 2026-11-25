// F607: original indexed fighter trajectory landing state 0x49.
// Whole source remains a nonexact giant; this is an inner case only.
case 0x49: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(hitReactionVelocityX);
        velocityY = hitReactionVelocityY;
        field05C = 0.8f;
        collisionResult = 0;
    }
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00=static_cast<short>((velocityX) * GeometryConstants::Hundred);
        scriptCounterF02=static_cast<short>((velocityY) * GeometryConstants::Hundred);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(animationStage-1);
    if (animationStage==1 && animationFrame==0 && velocityY != FloatConstants::Zero) {
        // Real VC7.1 left lvalue preserves original FLD global; FLD member.
        // Both branches exit this native case, not merely the nested if.
        if (*(&velocityX) == FloatConstants::Zero) {
            ResetSecondaryCounter(3);
            break;
        } else {
            ResetSecondaryCounter(2);
            break;
        }
    }
    break;
}
