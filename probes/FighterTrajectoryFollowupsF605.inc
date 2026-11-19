// F605: native second packed-switch actions 0x47 and 0x48 in large
// original fighter Advance() functions. These are NOT independent
// function credits; owner-specific spawn variants differ.
case 0x47: {
    // Original copying +0x98 to +0x54 is MOV dword, not FLD/FSTP.
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        reinterpret_cast<int&>(velocityY) = reinterpret_cast<int&>(field098);
        field05C = 0.8f;
        field07C = 0;
    }
    if (animationStage==F605_STAGE47 && velocityY < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F605_EARLY47);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F605_COUNTER) = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F605_COUNTER+2) = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        InitTrajectoryAt453E60(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame() == field070)
        SetAuxActionAt40FB40(F605_LATE47);
    break;
}
case 0x48: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        reinterpret_cast<int&>(velocityY) = reinterpret_cast<int&>(field098);
        field05C = 1.3f;
        field07C = 0;
    }
    if (animationStage==F605_STAGE48 && velocityY < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F605_EARLY48);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F605_COUNTER) = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F605_COUNTER+2) = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        InitTrajectoryAt453E60(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame() == field070)
        SetAuxActionAt40FB40(F605_LATE48);
    break;
}
