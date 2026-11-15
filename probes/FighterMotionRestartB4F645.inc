// F645 genuine original native B4/B5 motion restart and ground
// threshold transition. This is inside a giant fighter Advance()
// whole source TU that remains NONEXACT, not a callable leaf.
case F645_CASE: {
    if (animationStage==0 && animationFrame==0) {
        ResetAt453E20();
        velocityX=F645_START_POS;
        velocityY=12.5f;
        field05C=0.75f;
        reinterpret_cast<int&>(rotationZ)=0;
        ResetMotionAt40FC50();
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            y=0.0f;
            ResetAt453E20();
            break;
        }
    }
    if (GetNativeActionAt40FA30()==field070) {
        SetAuxActionAt40FB40(F645_AUX_ACTION);
        break;
    }
    break;
}
