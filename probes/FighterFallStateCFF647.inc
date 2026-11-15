// F647 original native action0xCF: source-level falling state,
// threshold clamp, frame finish. Full enclosing fighter NONEXACT.
case 0xCF: {
    field3AC=1;
    velocityX=(velocityX)-g_SubtractAt00657478;
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=0.0f;
        field3AC=0;
    }
    if (GetNativeActionAt40FA30()==field070) {
        SetNativeActionAt40FAC0(0);
        field3AC=0;
    }
    break;
}
