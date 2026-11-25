// Patchouli object action 0x352 at 0x0051497A–0x00514A9A (288 bytes).
case 0x352: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.5f;
        scaleY=0.5f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
    }
    scaleX=(scaleX)+FloatConstants::One;
    scaleY=(scaleY)+FloatConstants::One;
    if (animationStage>1) {
        if (color[0]>20)
            color[0]-=20;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
