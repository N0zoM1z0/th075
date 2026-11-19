// F598: real original fighter singleton 0x32/50, not a standalone function.
// Included inside the native 11-case switch; entire parent fighter remains
// an incomplete diagnostic C++ probe until all later actions are rebuilt.
case 0x32: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -8.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (CheckHorizontalLimits() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (AdvanceNestedFrame() == field070)
        ResetPrimaryCounters(0);
    break;
}
