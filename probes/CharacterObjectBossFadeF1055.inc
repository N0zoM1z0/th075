// F1055: one of the independently owned original 33C/33E/340/342/344
// character Object action interiors. Repeated C++ grammar: actual separate
// switch cases, no whole-game exact credit, native scaling and alpha fade.
case F1055_CASE: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    scaleX = (scaleX) * g_F1055_FadeScaleAt006598A4;
    scaleY = (scaleY) * g_F1055_FadeScaleAt006598A4;
    if (color[0] >= 20)
        color[0] -= 20;
    else
        color[0] = 0;
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
