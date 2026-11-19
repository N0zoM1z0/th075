// F961 real original Japanese 004AC040 stages 12F/130.
 // 12F: 004B12F1..004B13C0, 207 CODE B /59 x86 /6 original PE fields.
 // 130: 004B13C0..004B14C9, 265 CODE B /81 x86 /6 original PE fields.
 // Both are native GPR/mnemonic/width-complete INTERNAL cases,
 // not separate whole game functions; parent 82KB remains NONEXACT.
// Genuine original 004AC040 12F: native 207B/59x86.
case 0x12F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
            ClearMotionFields();
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(2);
    if ((animationStage)==4 && (animationFrame)==0)
        PrepareActionAt453D60(0x1C);
    break;
}
// Genuine original 004AC040 130: native 265B/81 x86, original sprite334.
case 0x130: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        y=0.0f;
        field05C=0.0f;
        velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==3 && (animationFrame)==0)
        PrepareActionAt453D60(0x1C);
    if ((animationStage)==3 && (animationFrame)==0) {
        SpawnSevenAt453B50(0x334,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1,0,1);
    }
    break;
}
