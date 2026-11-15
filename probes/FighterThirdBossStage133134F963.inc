// F963: original pinned Japanese TH075 004AC040 action 133 & 134.
 // 133 physically 004B1593..004B16AD 282 B/84 x86/7 typed PE fields;
 // 134 physically 004B16AD..004B18B1 516 B/152 x86/12 PE fields.
 // Natural C++ preserves all original mnemonic and width ordinals.
 // 53/98 GPR roles differ in still PARTIAL/nonexact 82KB father.
// F963 original 004AC040 stage133 native evidence, partial giant.
case 0x133: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0)
            ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D60(0x1C);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SpawnSevenAt453B50(0x324,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1,0,1);
    break;
}
// F963 original 004AC040 stage134 native evidence, partial giant.
case 0x134: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C)
        velocityX=(velocityX)-g_SubtractAt00657478;
    if ((velocityX)<g_StopThresholdAt00657480 &&
        y>g_ThresholdAt0065782C)
        velocityX=2.0f;
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<14) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            SetAuxActionAt40FB40(0xE);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=12.5f;
        velocityY=8.5f;
        field05C=0.65f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SpawnSevenAt453B50(0x336,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1,0,1);
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D60(0x1D);
    if ((reinterpret_cast<signed short&>(animationStage))==14 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40((reinterpret_cast<signed short&>(animationStage))-2);
    break;
}
