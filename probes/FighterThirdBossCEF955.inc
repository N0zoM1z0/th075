// F955 true original 004AC040 native action CE, 004B0BB8..004B0D42;
// 394 whole interior CODE B /115 x86 /9 genuine external PE fields.
// Genuine 0x3C projectile precedes stage-3 motion values, and
// this action has NO stage-4 auxiliary-speed test (unlike CC/CD).
// Natural case is embedded only in the still NONEXACT 82KB parent.
case 0xCE: {
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
    ++reinterpret_cast<signed short&>(animationFrame);
    if (reinterpret_cast<signed short&>(animationFrame)>=reinterpret_cast<signed short&>(field072)) {
        reinterpret_cast<signed short&>(animationFrame)=0;
        ++reinterpret_cast<signed short&>(animationStage);
        if (reinterpret_cast<signed short&>(animationStage)==3) {
            // Original native call before the actual motion values are reset.
            SpawnRawAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
            velocityX=-10.0f;
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
