// F617: one actual 101-x86 native air-transition case inside a giant
// fighter's second indexed action switch. Original owner parameters are
// established separately from the pinned PE. This is not an independent
// complete original function or adopted exact CODE.
case F617_CASE: {
    if (animationStage<F617_THRESHOLD && y>g_ThresholdAt0065782C) {
        velocityY = velocityY - field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ClearMotionFields();
            SetAuxActionAt40FB40(F617_THRESHOLD);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==field070) {
        SetNativeActionAt40FAC0(0);
        if (inputY>0)
            SetNativeActionAt40FAC0(1);
    }
    if (animationStage==field070-1) {
        // The native first comparison only skips the first assignment,
        // not the second comparison: two independent original ifs.
        // Retain the genuine source member lvalue to recover VC7.1 x87
        // evaluation order and original caller register roles.
        if (*(&x)>opponent->x)
            facing=-1;
        if (*(&x)<opponent->x)
            facing=1;
    }
    if (animationStage==F617_BEGIN_STAGE && animationFrame==0) {
        velocityY=F617_START_SPEED;
        velocityX=F617_START_POS;
        field05C=F617_FRICTION;
    }
    if (animationStage==F617_THRESHOLD && animationFrame==0)
        SetAuxActionAt40FB40(F617_FINISH_STATE);
    break;
}
