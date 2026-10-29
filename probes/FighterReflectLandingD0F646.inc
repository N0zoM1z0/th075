// F646 original native D0: reverse facing and x87 horizontal
// reflection, native conditional ground physics and aux-state exit.
// This is an original interior case, not an accepted entire giant.
case 0xD0: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        *reinterpret_cast<signed char*>(RAW+0x66) =
            -*reinterpret_cast<signed char*>(RAW+0x66);
        POS=-POS;
    }
    if (*(&POS5C)==g_ThresholdAt0065782C)
        POS5C=0.6f;
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        POS48=0.0f;
        ResetAt453E20();
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(5);
    break;
}
