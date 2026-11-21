// F965 original Japanese TH075 fighter 004AC040 native 186/187
// 186 at 004B1C5B..004B1D70, 277B/84x86/7 original PE fields;
// 187 at 004B1D70..004B1F1D, 429B/124x86/11 original PE fields.
// Both source states preserve original mnemonic+width geometry;
// native GPR roles still differ in the partial huge father (53/78).
// 186 has NO actual native afterRET label; original 136 134-x86
// true physical end supplies its source start. Never fabricate label.
// This is only internal C++ of still NONEXACT 82KB original fighter.
// Original Japanese 004AC040 handler 0x186, native 277B/84 x86.
case 0x186: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
            ClearMotionFields();
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
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0)
        PlaySharedSound(0x1C);
    if ((animationStage)==3 && (animationFrame)==0)
        Fighter::SpawnTrackedEffect(0x324,x,y,
            facing,1,0,1);
    break;
}
// Original Japanese 004AC040 handler 0x187, native 429B/124 x86.
case 0x187: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
        field080=2;
        field07C=0;
        velocityX=10.0f;
    }
    if ((animationStage)<2) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ResetSecondaryCounter(0xE);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=15.0f;
        velocityY=8.5f;
        field05C=0.6f;
    }
    if ((animationStage)==7 && (animationFrame)==0)
        PlaySharedSound(0x1C);
    if ((animationStage)==8 && (animationFrame)==0)
        field07C=0;
    if ((animationStage)==14 && (animationFrame)==0)
        ResetSecondaryCounter(0xC);
    break;
}
