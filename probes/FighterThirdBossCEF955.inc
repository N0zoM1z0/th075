// F955 true original 004AC040 native action CE, 004B0BB8..004B0D42;
// 394 whole interior CODE B /115 x86 /9 genuine external PE fields.
// Genuine 0x3C projectile precedes stage-3 motion values, and
// this action has NO stage-4 auxiliary-speed test (unlike CC/CD).
// Natural case is embedded only in the still NONEXACT 82KB parent.
case 0xCE: {
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
    ++animationFrame;
    if (animationFrame>=field072) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==3) {
            // Original native call before the actual motion values are reset.
            SpawnRawAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
            velocityX=-10.0f;
            velocityY=15.0f;
            field05C=0.7f;
            field3AC=0;
        }
        if (animationStage>=field070)
            animationStage=animationStage-2;
        BindAnimation();
    }
    break;
}
