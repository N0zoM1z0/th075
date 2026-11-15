// F1091: actual Japanese original 0x352 at 0051497A..00514A9A,
// 288 CODE B /64 x86 inside ONE still-NONEXACT 81KB boss.
case 0x352: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.5f;
        scaleY=0.5f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
    }
    scaleX=(scaleX)+g_F1051_ScaleCeilingAt0065747C;
    scaleY=(scaleY)+g_F1051_ScaleCeilingAt0065747C;
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>20)
            color[0]-=20;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
