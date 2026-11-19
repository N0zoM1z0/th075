// F841 selected original actor 0xCE native 387B/113 x86/8 real PE fields.
// Distinct stage3 native -11.0f X, +17.5f velocity, +0.8f drag.
// Real unconditional virtual frame method, native x87 operand order.
// Interior case only, no independently callable exact CODE.
case 0xCE: {
    if (y==g_ThresholdAt0065782C || velocityY>g_ThresholdAt0065782C) {
        SetupCollisionAt454BC0(3,4,0xFF);
        field088=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ClearMotionFields();
    if (animationStage>2) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            y=0.0f;
            ClearMotionFields();
            return;
        }
    }
    ++animationFrame;
    if (animationFrame>=field072) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==3) {
            velocityX=-11.0f;
            velocityY=17.5f;
            field05C=0.8f;
            SpawnRawAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
            field3AC=0;
        }
        if (animationStage>=field070)
            animationStage=animationStage-2;
        BindAnimation();
    }
    return;
}
