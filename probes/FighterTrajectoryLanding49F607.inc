// F607: original indexed fighter trajectory landing state 0x49.
// Whole source remains a nonexact giant; this is an inner case only.
case 0x49: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(field094);
        velocityY = field098;
        field05C = 0.8f;
        field07C = 0;
    }
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F607_COUNTER)=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F607_COUNTER+2)=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame()==field070)
        ResetSecondaryCounter(animationStage-1);
    if (animationStage==1 && animationFrame==0 && velocityY != g_ThresholdAt0065782C) {
        // Real VC7.1 left lvalue preserves original FLD global; FLD member.
        // Both branches exit this native case, not merely the nested if.
        if (*(&velocityX) == g_ThresholdAt0065782C) {
            ResetSecondaryCounter(3);
            break;
        } else {
            ResetSecondaryCounter(2);
            break;
        }
    }
    break;
}
