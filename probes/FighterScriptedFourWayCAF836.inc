// F836: actual Japanese TH075 005214B0 native interior CA.
// Native 418 B/121 x86/11 physical PE fields; direct enclosing-giant exits.
// Unlike another fighter, resets native motion slots, with stage2 sprite.
// Not independently callable original CODE.
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)>1) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            animationFrame=0;
            SetNativeActionAt40FAC0(0xA);
            return;
        }
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(9);
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=10.0f;
        velocityY=5.0f;
        field05C=0.6f;
        SpawnAt453C80(0x7D,float((facing)*80)+(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
        PlaySharedSound(31);
    }
    return;
}
