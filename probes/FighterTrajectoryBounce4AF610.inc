// F610 original native fighter second-switch action 0x4A inside whole
// incomplete giant Advance() C++ source; not an independent function.
case 0x4A: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        reinterpret_cast<int&>(velocityY) = reinterpret_cast<int&>(field098);
        field05C = 0.8f;
        field07C = 0;
    }
    if (animationStage==F610_STAGE && velocityY < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F610_EARLY);
        break;
    }
    if (ContactAt454EE0() && (velocityX) <= g_BounceThresholdAt006590C0) {
        SetNativeActionAt40FAC0(0x4C);
        velocityX = -(velocityX) * g_BounceScaleAt00657F74;
        velocityY = 15.0f;
        field05C = 0.5f;
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        I16(F610_COUNTER) = 0;
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
#if F610_PREPARE_BEFORE
        PrepareActionAt453D60(0x16);
#endif
        I16(F610_COUNTER)=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F610_COUNTER+2)=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
#if !F610_PREPARE_BEFORE
        PrepareActionAt453D60(0x16);
#endif
        break;
    }
    if (GetNativeActionAt40FA30()==field070)
        SetAuxActionAt40FB40(F610_LATE);
    break;
}
