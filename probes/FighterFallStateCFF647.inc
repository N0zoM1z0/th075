// F647 original native action0xCF: source-level falling state,
// threshold clamp, frame finish. Full enclosing fighter NONEXACT.
case 0xCF: {
    field3AC=1;
    velocityX=(velocityX)-g_SubtractAt00657478;
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=0.0f;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==field070) {
        ResetPrimaryCounters(0);
        field3AC=0;
    }
    break;
}
