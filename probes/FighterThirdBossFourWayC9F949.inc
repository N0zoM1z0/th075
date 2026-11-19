// F949: independent native 004AC040 original C9
// 004B02B9..004B04CC 531 complete internal original CODE B/158 x86.
// Natural source preserves all original positional mnemonic, width
// and GPR roles in the whole incomplete 82KB game-fighter source.
// All 13 original PE call/global targets must be verified separately;
// original saved-this EBP-0x64 is still wrong in this partial parent.
// No independent callable function or whole-fighter exactness claim.
case 0xC9: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0)
        ClearMotionFields();
    if ((animationStage)==2 && (animationFrame)==0)
        velocityX=0.0f;
    if ((animationStage)==4 && (animationFrame)==0)
        velocityX=-10.0f;
    if (y>g_ThresholdAt0065782C && (animationStage)>3 && (animationStage)<6) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            animationFrame=0;
            SetAuxActionAt40FB40(6);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==2 && (animationFrame)==0)
        velocityX=-50.0f;
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityY=4.0f;
        field05C=0.6f;
        velocityX=-30.0f;
        SpawnMixedAt453C80(0x7D,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            -(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            -(facing),1);
        PlaySharedSound(31);
    }
    if ((animationStage)==6 && (animationFrame)==0)
        SetAuxActionAt40FB40(5);
    break;
}
