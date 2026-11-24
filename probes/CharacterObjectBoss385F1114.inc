// F1114: genuine original Japanese action 0x385 at 0051AFF0..0051B21D:
// 557 original CODE bytes/114 x86, in ONE NONEXACT 81KB game callable.
case 0x385: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (field07C==6) {
        ++field080;
        field07C=0;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        scaleX=1.0f;
        scaleY=2.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=15.0f;
    }
    if (animationStage==2) {
        scaleX=float(RecordedRange(0,6))*
            FloatConstants::OneTenth+g_F1114_RandomOffsetAt00659094;
        scaleY=(*(&scaleX))+FloatConstants::One;
    }
    if (animationStage>2)
        scaleX=(scaleX)*g_F1114_FadeAt00659240;
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==3 && animationFrame==0) {
        if (field0D8<9) {
            ++field0D8;
            ResetSecondaryCounter(2);
        } else {
            scaleX=1.8f;
            scaleY=1.0f;
        }
    }
    return;
}
