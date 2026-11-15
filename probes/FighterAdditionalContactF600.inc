// F600: real consecutive native second-switch contact states of eleven
// fighter bosses. These cases are inside the incomplete whole function,
// NOT independent functions or accepted authored original CODE.
// Stage-7 variants use the native counter offset supplied by the owner:
// +0xEFC for fighter 005AEEC0 and +0xF00 for the other ten giants.
// Source is natural VC7.1 C++; original PE controls comparison.

case 0x33: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -9.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x34: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -12.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x35: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        I16(CONTACT_STAGE_OFFSET) = 0;
        velocityX = -15.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070)) {
        SetNativeActionAt40FAC0(0);
        I16(CONTACT_STAGE_OFFSET) = 0;
        break;
    }
    if (reinterpret_cast<signed short&>(animationStage) == 7 && I16(CONTACT_STAGE_OFFSET) < 1) {
        ++I16(CONTACT_STAGE_OFFSET);
        SetAuxActionAt40FB40(1);
    }
    break;
}

case 0x38: {
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
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x39: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -9.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x3A: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -12.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x3B: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        I16(CONTACT_STAGE_OFFSET) = 0;
        velocityX = -15.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070)) {
        SetNativeActionAt40FAC0(0);
        I16(CONTACT_STAGE_OFFSET) = 0;
        break;
    }
    if (reinterpret_cast<signed short&>(animationStage) == 7 && I16(CONTACT_STAGE_OFFSET) < 1) {
        ++I16(CONTACT_STAGE_OFFSET);
        SetAuxActionAt40FB40(1);
    }
    break;
}

case 0x3E: {
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
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(2);
    break;
}

case 0x3F: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -9.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(2);
    break;
}

case 0x40: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        velocityX = -12.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070))
        SetNativeActionAt40FAC0(2);
    break;
}

case 0x41: {
    if (reinterpret_cast<signed short&>(animationStage) == 0 && reinterpret_cast<signed short&>(animationFrame) == 0) {
        I16(CONTACT_STAGE_OFFSET) = 0;
        velocityX = -15.0f;
        velocityY = 0.0f;
        field07C = 0;
    }
    if ((velocityX) < g_ThresholdAt0065782C) {
        velocityX = (velocityX) + g_ApproachAt00658058;
        if ((velocityX) > g_ThresholdAt0065782C)
            velocityX = 0.0f;
    }
    if (ContactAt454EE0() &&
        field3BE) {
        field490 =
            static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == reinterpret_cast<signed short&>(field070)) {
        SetNativeActionAt40FAC0(0);
        I16(CONTACT_STAGE_OFFSET) = 0;
        break;
    }
    if (reinterpret_cast<signed short&>(animationStage) == 7 && I16(CONTACT_STAGE_OFFSET) < 1) {
        ++I16(CONTACT_STAGE_OFFSET);
        SetAuxActionAt40FB40(1);
    }
    break;
}
