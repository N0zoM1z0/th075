// F606: exact original 113-instruction case0x48 variant where the
// stage-one projectile guard occurs AFTER the early transition.
// Caller declares the true case,
// original drag, projectile kind, one-shot side and stage policy.
// Each inclusion is a naturally-typed C++ case inside whole Advance().
// These are NOT independently callable or accepted whole functions.
case F606_ACTION: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = F606_DRAG;
        I32(0x7C) = 0;
    }
    if (I16(0x62)==F606_STAGE && POS54<g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F606_EARLY);
        break;
    }
    if (I16(0x62)==1 && I16(0x64)==0 && I16(0xF0C)==0) {
        I16(0xF0C)=1;
        SpawnDirectedAt453A70(F606_PROJECTILE,
            I32(0x44), I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66), F606_SIDE);
    }
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F606_COUNTER)=static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F606_COUNTER+2)=static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(F606_LATE);
    break;
}
