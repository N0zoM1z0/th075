// F953 original Japanese TH075 giant 004AC040 action 0xCD native
// 435 complete inner CODE B /128 x86 and 11 true original typed
// PE external fields; this is NOT an independent whole function.
// Real state transition fires raw 0x3C projectile BEFORE writing
// the new frame/trajectory values. Full 82KB parent remains NONEXACT.
case 0xCD: {
    if ((*(&y) == g_ThresholdAt0065782C) ||
        velocityY > g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
        reinterpret_cast<signed short&>(field088)=2;
    }
    if (reinterpret_cast<signed short&>(animationStage)==0 && (field3AC)==0)
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
    if (reinterpret_cast<signed short&>(animationStage)==4 &&
        velocityY<g_ExtraThresholdAt00657D14)
        SetAuxActionAt40FB40(5);
    ++reinterpret_cast<signed short&>(animationFrame);
    if (reinterpret_cast<signed short&>(animationFrame)>=reinterpret_cast<signed short&>(field072)) {
        reinterpret_cast<signed short&>(animationFrame)=0;
        ++reinterpret_cast<signed short&>(animationStage);
        if (reinterpret_cast<signed short&>(animationStage)==2) {
            // Original native call before the actual motion values are reset.
            SpawnRawAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
            velocityX=10.0f;
            velocityY=15.0f;
            field05C=0.7f;
            field3AC=0;
        }
        if (reinterpret_cast<signed short&>(animationStage)>=reinterpret_cast<signed short&>(field070))
            reinterpret_cast<signed short&>(animationStage)=reinterpret_cast<signed short&>(animationStage)-2;
        BindAnimation();
    }
    break;
}
