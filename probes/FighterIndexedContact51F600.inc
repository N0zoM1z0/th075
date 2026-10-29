// F600: real complete second-switch indexed action 0x33/51, not a
// standalone native function. The original indexed case starts with -9.0f,
// while neighboring singleton 0x32 starts with -8.0f. Do not fold cases.
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
