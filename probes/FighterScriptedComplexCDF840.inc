// F840 original 005214B0 native CD 387 CODE B/113 x86/8 PE fields.
// Stage3 native velocityX 11, velocity17.5, drag0.8, original vtable call
// outside conditional subtract; native stage3-only field3AC clear.
// Original game interior, not independently callable exact CODE.
case 0xCD: {
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
            velocityX=11.0f;
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
