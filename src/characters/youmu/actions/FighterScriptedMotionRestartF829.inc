// F829 actual native B4/B5 215B/60x86/8 physical PE fields, void-source direct original parent epilogue exits. Interior only.
// F645 genuine original native B4/B5 motion restart and ground
// threshold transition. This is inside a giant fighter Advance()
// whole source TU that remains NONEXACT, not a callable leaf.
case F645_CASE: {
    if (animationStage==0 && animationFrame==0) {
        ClearMotionFields();
        velocityX=F645_START_POS;
        velocityY=12.5f;
        verticalAcceleration=0.75f;
        rotationZ=0.0f;
        ClearTransformFlag();
    }
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-verticalAcceleration;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetSecondaryCounter(F645_AUX_ACTION);
        return;
    }
    return;
}
