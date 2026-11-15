// F598: real original fighter singleton 0x32/50, not a standalone function.
// Included inside the native 11-case switch; entire parent fighter remains
// an incomplete diagnostic C++ probe until all later actions are rebuilt.
case 0x32: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -8.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    break;
}
