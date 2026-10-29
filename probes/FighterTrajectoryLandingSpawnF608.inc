// F608: original native 118-instruction indexed action0x49 in two
// special spawning fighter giants. Original whole boss remains NONEXACT.
case 0x49: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 0.8f;
        I32(0x7C) = 0;
    }
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F608_COUNTER)=static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F608_COUNTER+2)=static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(I16(0x62)-1);
    if (I16(0x62)==1 && I16(0x64)==0) {
        // Actual 118-x86 native case has a once-only projectile branch
        // before its two original x87 equality tests. Keep it inside
        // the already established stage-one/frame-zero guard.
        if (I16(0xF0C)==0) {
            I16(0xF0C)=1;
            SpawnDirectedAt453A70(F608_PROJECTILE,
                I32(0x44), I32(0x48),
                *reinterpret_cast<signed char*>(RAW+0x66), F608_SIDE);
        }
        if (POS54 != g_ThresholdAt0065782C) {
        // Real VC7.1 left lvalue preserves original FLD global; FLD member.
        // Both branches exit this native case, not merely the nested if.
        if (*(&POS) == g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(3);
            break;
        } else {
            SetAuxActionAt40FB40(2);
            break;
        }
        }
    }
    break;
}
