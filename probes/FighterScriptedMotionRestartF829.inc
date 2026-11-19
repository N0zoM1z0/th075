// F829 actual native B4/B5 215B/60x86/8 physical PE fields, void-source direct original parent epilogue exits. Interior only.
// F645 genuine original native B4/B5 motion restart and ground
// threshold transition. This is inside a giant fighter Advance()
// whole source TU that remains NONEXACT, not a callable leaf.
case F645_CASE: {
    if (animationStage==0 && animationFrame==0) {
        ClearMotionFields();
        velocityX=F645_START_POS;
        velocityY=12.5f;
        field05C=0.75f;
        reinterpret_cast<int&>(rotationZ)=0;
        ClearTransformFlag();
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070) {
        ResetSecondaryCounter(F645_AUX_ACTION);
        return;
    }
    return;
}
