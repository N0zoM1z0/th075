// F600: real consecutive native second-switch contact states of eleven
// fighter bosses. Every terminal path returns from the native parent;
// the partial parent's shared default frame handler is only for unmapped
// actions. These are not independent functions or accepted authored CODE.
// Stage-7 variants use the native counter offset supplied by the owner:
// +0xEFC for fighter 005AEEC0 and +0xF00 for the other ten giants.
// Source is natural VC7.1 C++; original PE controls comparison.

case 0x33: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -9.0f;
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(0);
    return;
}

case 0x34: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -12.0f;
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(0);
    return;
}

case 0x35: {
    if (animationStage == 0 && animationFrame == 0) {
        scriptCounterF00 = 0;
        velocityX = -15.0f;
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
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        scriptCounterF00 = 0;
        return;
    }
    if (animationStage == 7 && scriptCounterF00 < 1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    return;
}

case 0x38: {
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(0);
    return;
}

case 0x39: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -9.0f;
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(0);
    return;
}

case 0x3A: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -12.0f;
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(0);
    return;
}

case 0x3B: {
    if (animationStage == 0 && animationFrame == 0) {
        scriptCounterF00 = 0;
        velocityX = -15.0f;
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
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        scriptCounterF00 = 0;
        return;
    }
    if (animationStage == 7 && scriptCounterF00 < 1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    return;
}

case 0x3E: {
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(2);
    return;
}

case 0x3F: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -9.0f;
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(2);
    return;
}

case 0x40: {
    if (animationStage == 0 && animationFrame == 0) {
        velocityX = -12.0f;
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
    if (AdvanceNestedFrame() == animationStageCount)
        ResetPrimaryCounters(2);
    return;
}

case 0x41: {
    if (animationStage == 0 && animationFrame == 0) {
        scriptCounterF00 = 0;
        velocityX = -15.0f;
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
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
        scriptCounterF00 = 0;
        return;
    }
    if (animationStage == 7 && scriptCounterF00 < 1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    return;
}
