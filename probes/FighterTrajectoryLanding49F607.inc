// F607: original indexed fighter trajectory landing state 0x49.
// Whole source remains a nonexact giant; this is an inner case only.
case 0x49: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 0.8f;
        I32(0x7C) = 0;
    }
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F607_COUNTER)=static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F607_COUNTER+2)=static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(I16(0x62)-1);
    if (I16(0x62)==1 && I16(0x64)==0 && POS54 != g_ThresholdAt0065782C) {
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
    break;
}
