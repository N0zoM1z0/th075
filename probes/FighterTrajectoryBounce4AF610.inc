// F610 original native fighter second-switch action 0x4A inside whole
// incomplete giant Advance() C++ source; not an independent function.
case 0x4A: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(field094);
        velocityY = field098;
        field05C = 0.8f;
        field07C = 0;
    }
    if (animationStage==F610_STAGE && velocityY < g_StopThresholdAt00657480) {
        ResetSecondaryCounter(F610_EARLY);
        break;
    }
    if (CheckHorizontalLimits() && (velocityX) <= g_BounceThresholdAt006590C0) {
        ResetPrimaryCounters(0x4C);
        velocityX = -(velocityX) * g_BounceScaleAt00657F74;
        velocityY = 15.0f;
        field05C = 0.5f;
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        I16(F610_COUNTER) = 0;
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
#if F610_PREPARE_BEFORE
        PlaySharedSound(0x16);
#endif
        I16(F610_COUNTER)=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F610_COUNTER+2)=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
#if !F610_PREPARE_BEFORE
        PlaySharedSound(0x16);
#endif
        break;
    }
    if (AdvanceNestedFrame()==field070)
        ResetSecondaryCounter(F610_LATE);
    break;
}
