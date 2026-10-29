// F647 original native action0xCF: source-level falling state,
// threshold clamp, frame finish. Full enclosing fighter NONEXACT.
case 0xCF: {
    FLAG=1;
    POS=POS-g_SubtractAt00657478;
    if (POS<g_ThresholdAt0065782C) {
        POS=0.0f;
        FLAG=0;
    }
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        SetNativeActionAt40FAC0(0);
        FLAG=0;
    }
    break;
}
