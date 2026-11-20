// F1092: actual Japanese original 0x353 at 00514A9A..00514B35,
// 155 CODE B /35 x86 inside ONE still-NONEXACT 81KB boss.
case 0x353: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
