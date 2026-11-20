// F831 real original 005214B0 interior 0xCF 114 CODE B/30 x86/4 native PE fields.
// Normal direct exit from encompassing void whole fighter; NOT a callable original function.
// F647 original native action0xCF: source-level falling state,
// threshold clamp, frame finish. Full enclosing fighter NONEXACT.
case 0xCF: {
    field3AC=1;
    velocityX=(velocityX)-g_SubtractAt00657478;
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=0.0f;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetPrimaryCounters(0);
        field3AC=0;
    }
    return;
}
