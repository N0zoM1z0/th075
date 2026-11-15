// F867 original native 1F5 628B/195x86/17 physically correct PE fields.
// Original stage1/2/13/14/15/24 separate checks, native char fourth parameter.
// Native lower height comparator global 657480, not apparent equivalent 65782C.
// Full enclosing fighter still GPR and final JMP nonexact.
case 0x1F5: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetAt453E20();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_F866DropAt006583FC;
        if ((velocityX)<g_StopThresholdAt00657480)
            velocityX=2.0f;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0x18);
            y=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==1 && (animationFrame)==0) {
        velocityX=9.5f;
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        SpawnDirectedAt453A70(0x33B,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(1);
    }
    if ((animationStage)==0xD && (animationFrame)==0) {
        SpawnDirectedAt453A70(0x338,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(1);
    }
    if ((animationStage)==0xE && (animationFrame)==0) {
        field080=1;
        field07C=0;
    }
    if ((animationStage)==0xF && (animationFrame)==0) {
        velocityX=10.0f;
        velocityY=15.0f;
        field05C=0.65f;
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    }
    if ((animationStage)==0x18 && (animationFrame)==0)
        SetAuxActionAt40FB40(0x16);
    return;
}
