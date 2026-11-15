// F839 real original selected 005214B0 caseCC 428B/126-x86/10 real PE fields.
// Native float evaluation order y+velocityY and vtable call OUTSIDE
// conditional stage-short decrement. Genuine direct parent exits.
// Not an independently callable original game function.
case 0xCC: {
    if (y==g_ThresholdAt0065782C || velocityY>g_ThresholdAt0065782C) {
        SetupCollisionAt454BC0(3,4,0xFF);
        reinterpret_cast<signed short&>(field088)=2;
    }
    if (reinterpret_cast<signed short&>(animationStage)==0 && (field3AC)==0)
        ResetAt453E20();
    if (reinterpret_cast<signed short&>(animationStage)>2) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            y=0.0f;
            ResetAt453E20();
            return;
        }
    }
    if (reinterpret_cast<signed short&>(animationStage)==4 && velocityY<g_ExtraThresholdAt00657D14)
        SetAuxActionAt40FB40(5);
    ++reinterpret_cast<signed short&>(animationFrame);
    if (reinterpret_cast<signed short&>(animationFrame)>=reinterpret_cast<signed short&>(field072)) {
        reinterpret_cast<signed short&>(animationFrame)=0;
        ++reinterpret_cast<signed short&>(animationStage);
        if (reinterpret_cast<signed short&>(animationStage)==3) {
            velocityX=0.0f;
            velocityY=23.0f;
            field05C=0.75f;
            SpawnRawAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
            field3AC=0;
        }
        if (reinterpret_cast<signed short&>(animationStage)>=reinterpret_cast<signed short&>(field070))
            reinterpret_cast<signed short&>(animationStage)=reinterpret_cast<signed short&>(animationStage)-2;
        BindAnimation();
    }
    return;
}
