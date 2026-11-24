// F647 original native action0xCF: source-level falling state,
// threshold clamp, frame finish. Full enclosing fighter NONEXACT.
case 0xCF: {
    field3AC=1;
    velocityX=(velocityX)-FloatConstants::Half;
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=0.0f;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetPrimaryCounters(0);
        field3AC=0;
    }
    break;
}
