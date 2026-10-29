// F617: one actual 101-x86 native air-transition case inside a giant
// fighter's second indexed action switch. Original owner parameters are
// established separately from the pinned PE. This is not an independent
// complete original function or adopted exact CODE.
case F617_CASE: {
    if (I16(0x62)<F617_THRESHOLD && POS48>g_ThresholdAt0065782C) {
        POS54 = POS54 - POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(F617_THRESHOLD);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        SetNativeActionAt40FAC0(0);
        if (I32(0x4E0)>0)
            SetNativeActionAt40FAC0(1);
    }
    if (I16(0x62)==I16(0x70)-1) {
        // The native first comparison only skips the first assignment,
        // not the second comparison: two independent original ifs.
        // Retain the genuine source member lvalue to recover VC7.1 x87
        // evaluation order and original caller register roles.
        if (*(&F32(0x44))>*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=-1;
        if (*(&F32(0x44))<*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=1;
    }
    if (I16(0x62)==F617_BEGIN_STAGE && I16(0x64)==0) {
        POS54=F617_START_SPEED;
        POS=F617_START_POS;
        POS5C=F617_FRICTION;
    }
    if (I16(0x62)==F617_THRESHOLD && I16(0x64)==0)
        SetAuxActionAt40FB40(F617_FINISH_STATE);
    break;
}
