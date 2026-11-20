// F964 real Japanese TH075 original fighter 004AC040 stages 135/136.
 // Original 135 physical 004B18B1..004B1A98, 487B/137x86/12 PE fields.
 // Compiled source 481B/137x86; two -0xA4 long EBP scratch widths
 // account for 6 missing original bytes, with 89 wrong GPR roles.
 // Original 136 physical 004B1A98..004B1C5B, 451B/134x86/11 PE fields.
 // Compiled source 451B/134x86, zero wrong mnemonic/width positions,
 // 84 wrong GPR roles. Native 136 uses FLOAT EQUALITY on +0x48
 // (FUCOMPP/TEST AH,44h) in the genuine falling-flag branch.
 // Original 136->186 physical boundary has no separate afterRET label;
 // do not invent a switch entry or accept internal code as whole exact.
// Original third-fighter native game action 135, candidate.
case 0x135: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
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
    if ((animationStage)==3 || (animationStage)==4) {
        velocityY=velocityY-g_AnimationDeltaAt0065747C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(5);
            SpawnAuxEffect(0x80,
                float((facing)*150)+(x),
                y,facing,1);
            break;
        }
    }
    if ((animationStage)>4) {
        velocityX=(velocityX)-g_F964_LateFallAt00658048;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=15.0f;
        velocityY=4.5f;
        field3AC=0;
    }
    if ((animationStage)==5 && (animationFrame)==0)
        velocityX=4.0f;
    break;
}
// Original third-fighter native game action 136, candidate.
case 0x136: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=2;
        field07C=0;
    }
    if ((field3AC)>0 && y==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<12) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(0xC);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        velocityX=4.0f;
        velocityY=9.5f;
        field05C=1.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        Fighter::SpawnTrackedEffect(0x337,x,y,
            facing,1,0,1);
    }
    if ((animationStage)==9 && (animationFrame)==0)
        field07C=0;
    break;
}
