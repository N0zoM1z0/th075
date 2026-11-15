// F966 original Japanese TH075 004AC040 actions 188/189.
// 188 physical 004B1F1D..004B2091 372B/106x86/11 PE external fields;
// 189 physical 004B2091..004B2167 214B/61x86/6 PE fields.
// Ordinary C++ emits native mnemonic/widths exactly in whole partial
// fighter; 63/38 GPR-role errors remain. 188 has genuine FUCOMPP
// float equality and real stage6->stage4 nested control-flow test;
// do NOT silently optimize away an original native branch.
// The entire original 82KB fighter function remains NONEXACT.
// Real original Japanese TH075 004AC040 0x188 372B/106-x86 source.
case 0x188: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
            ResetAt453E20();
        field080=1;
        field07C=0;
        velocityX=10.0f;
    }
    if (y==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            y=0.0f;
            SetAuxActionAt40FB40(0xC);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        // Actual original PE retains this inner stage 4 conditional,
        // despite the outer stage 6 test. Do not delete original branch.
        if ((animationStage)==4 && (animationFrame)==0)
            PrepareActionAt453D60(0x1C);
        velocityX=10.0f;
        velocityY=12.5f;
        field05C=1.0f;
    }
    break;
}
// Real original Japanese TH075 004AC040 0x189 214B/61-x86 source.
case 0x189: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
            ResetAt453E20();
        field080=1;
        field07C=0;
        velocityX=10.0f;
    }
    if ((animationStage)>0) {
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
