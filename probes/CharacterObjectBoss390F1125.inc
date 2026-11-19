// F1125 original Japanese action 0x390 at 0051CB4A..0051CF28:
// 990 native CODE B /212 x86 inside ONE still-NONEXACT 81KB boss.
case 0x390: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        SetPolarVelocity(field0C8,
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+g_F1085_LastYAt006592A4);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
    }
    ++field0D8;
    if (animationStage<2) {
        SetPolarVelocity(field0C8,
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+g_F1085_LastYAt006592A4);
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (field07C!=0 && animationStage==1) {
        ResetSecondaryCounter(2);
        scaleX=4.0f;
        scaleY=4.0f;
        velocityX=0.0f;
        velocityY=0.0f;
        return;
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1125_YUpperAt00657884 ||
        y<g_F1101_LeftAt0065924C) {
        ClearFrameInfo();
        return;
    }
    if (animationStage>1) {
        if (color[0]>=25) {
            color[0]-=25;
            color[1]-=25;
            color[2]-=25;
            scaleX=(scaleX)*g_F1070_FadeScaleAt00659454;
            scaleY=(scaleY)*g_F1070_FadeScaleAt00659454;
        } else {
            color[0]=0;
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
