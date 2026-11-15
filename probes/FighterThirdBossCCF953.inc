// F953 original Japanese TH075 giant 004AC040 action 0xCC native
// 435 complete inner CODE B /128 x86 and 11 true original typed
// PE external fields; this is NOT an independent whole function.
// Real state transition fires raw 0x3C projectile BEFORE writing
// the new frame/trajectory values. Full 82KB parent remains NONEXACT.
case 0xCC: {
    if ((*(&y) == g_ThresholdAt0065782C) ||
        velocityY > g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
        field088=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ResetAt453E20();
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(10);
            y=0.0f;
            ResetAt453E20();
            break;
        }
    }
    if (animationStage==4 &&
        velocityY<g_ExtraThresholdAt00657D14)
        SetAuxActionAt40FB40(5);
    ++animationFrame;
    if (animationFrame>=field072) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==3) {
            // Original native call before the actual motion values are reset.
            SpawnRawAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
            velocityX=0.0f;
            velocityY=20.0f;
            field05C=0.7f;
            field3AC=0;
        }
        if (animationStage>=field070)
            animationStage=animationStage-2;
        BindAnimation();
    }
    break;
}
