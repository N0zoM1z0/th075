// F1080 real original Japanese action 0x348: PE 005125A8..00512815,
// 621 native CODE B / 132 x86 inside ONE still nonexact 81KB game callable.
case 0x348: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
    }
    SetPolarVelocity(
        float(owner->fieldF0E)+
             g_F1080_ParentScaleAt006590A8*static_cast<const float&>(field0C8),
        float(field0D8));
    if (field0D8<120)
        field0D8=short(field0D8+20);
    if (field0D8>120)
        field0D8=120;
    x=velocityX+owner->x;
    y=velocityY+owner->y+g_F1057_YOffsetAt00657888;
    rotationZ=(rotationZ)+g_F1080_AngleIncreaseAt00657850;
    if (animationStage==1) {
        if (owner->action!=0x2BE ||
            (owner->action==0x2BE &&
             owner->animationStage>8))
            ResetSecondaryCounter(2);
    }
    if (animationStage>1) {
        if (color[0]>25)
            color[0]-=25;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
