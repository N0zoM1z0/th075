// F646 original native D0: reverse facing and x87 horizontal
// reflection, native conditional ground physics and aux-state exit.
// This is an original interior case, not an accepted entire giant.
case 0xD0: {
    if (animationStage==0 && animationFrame==0) {
        facing =
            -facing;
        velocityX=-(velocityX);
    }
    if (*(&field05C)==g_ThresholdAt0065782C)
        field05C=0.6f;
    velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        y=0.0f;
        ClearMotionFields();
        break;
    }
    if (AdvanceNestedFrame()==field070)
        SetAuxActionAt40FB40(5);
    break;
}
