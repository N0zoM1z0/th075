// F613 real native second indexed-switch recovery action0x4C within giant
// fighter Advance(). Original whole giant is still NONEXACT; case alone
// is not independently callable source CODE and has separate jump DATA.
case 0x4C: {
    if (scriptCounterF00==0) {
        ++scriptCounterF00;
        ResetTransform(0.0f,95.0f,0.0f);
    }
    // Original PE executes this global angle advance on *every* frame,
    // even when the once-only F613_COUNTER initialization is skipped.
    rotationZ = (rotationZ) + g_AngleShiftAt00657878;
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        PlaySharedSound(0x16);
        scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        rotationZ=0.0f;
        SetCameraShake(2.0f);
        ClearTransformFlag();
        break;
    }
    if (AdvanceNestedFrame() == field070)
        ResetSecondaryCounter(0);
    break;
}
