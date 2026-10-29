// F600: real consecutive native second-switch contact states of eleven
// fighter bosses. These cases are inside the incomplete whole function,
// NOT independent functions or accepted authored original CODE.
// Stage-7 variants use the native counter offset supplied by the owner:
// +0xEFC for fighter 005AEEC0 and +0xF00 for the other ten giants.
// Source is natural VC7.1 C++; original PE controls comparison.

case 0x33: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -9.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x34: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -12.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x35: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        I16(CONTACT_STAGE_OFFSET) = 0;
        POS = -15.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70)) {
        SetNativeActionAt40FAC0(0);
        I16(CONTACT_STAGE_OFFSET) = 0;
        break;
    }
    if (I16(0x62) == 7 && I16(CONTACT_STAGE_OFFSET) < 1) {
        ++I16(CONTACT_STAGE_OFFSET);
        SetAuxActionAt40FB40(1);
    }
    break;
}

case 0x38: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -8.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x39: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -9.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x3A: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -12.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}

case 0x3B: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        I16(CONTACT_STAGE_OFFSET) = 0;
        POS = -15.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70)) {
        SetNativeActionAt40FAC0(0);
        I16(CONTACT_STAGE_OFFSET) = 0;
        break;
    }
    if (I16(0x62) == 7 && I16(CONTACT_STAGE_OFFSET) < 1) {
        ++I16(CONTACT_STAGE_OFFSET);
        SetAuxActionAt40FB40(1);
    }
    break;
}

case 0x3E: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -8.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(2);
    break;
}

case 0x3F: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -9.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(2);
    break;
}

case 0x40: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        POS = -12.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetNativeActionAt40FAC0(2);
    break;
}

case 0x41: {
    if (I16(0x62) == 0 && I16(0x64) == 0) {
        I16(CONTACT_STAGE_OFFSET) = 0;
        POS = -15.0f;
        POS54 = 0.0f;
        I32(0x7C) = 0;
    }
    if (POS < g_ThresholdAt0065782C) {
        POS = POS + g_ApproachAt00658058;
        if (POS > g_ThresholdAt0065782C)
            POS = 0.0f;
    }
    if (ContactAt454EE0() &&
        *reinterpret_cast<signed char*>(RAW + 0x3BE)) {
        *reinterpret_cast<float*>(RAW + 0x490) =
            static_cast<float>(POS * g_ContactScaleAt006583E8);
    }
    if (GetNativeActionAt40FA30() == I16(0x70)) {
        SetNativeActionAt40FAC0(0);
        I16(CONTACT_STAGE_OFFSET) = 0;
        break;
    }
    if (I16(0x62) == 7 && I16(CONTACT_STAGE_OFFSET) < 1) {
        ++I16(CONTACT_STAGE_OFFSET);
        SetAuxActionAt40FB40(1);
    }
    break;
}
