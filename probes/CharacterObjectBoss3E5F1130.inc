// F1130: original Japanese 0x3E5 at 0051E01F..0051E215:
// 502 native original CODE B /96 x86 inside ONE nonexact 81KB Boss.
case 0x3E5: {
    x = owner->x;
    y=0.0f;
    field08A=1;
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=3.0f;
        scaleY=3.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field01A=0x4E2;
        rotationY=0.0f;
        rotationZ=0.0f;
        rotationX=-80.0f;
        field0D8=owner->field3A0;
    }
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    scaleX=float(owner->field3A0)/field0D8*2.0f;
    scaleY=float(owner->field3A0)/field0D8*2.0f;
    rotationZ=(rotationZ)+g_F1051_ScaleCeilingAt0065747C;
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetSecondaryCounter(10);
        return;
    }
    return;
}
