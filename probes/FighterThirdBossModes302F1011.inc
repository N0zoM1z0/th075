// F1011 original Japanese 004AC040 fighter 302.
 // Native 004BF9A2..004BFDAB: 1033B/279 x86/25 PE.
 // Four authentic mode0/1/2/3 signed shot loops of
 // 10/12/15/20 sprite0x389, step36/30/24/18,
 // FILD facing*16 FSUBR world-X and Y+0065836C,
 // native motion threshold and ground return.
 // All 279 original mnemonic/GPR roles, only
 // last shared-tail JMP width native5 vs source2.
 // Adding genuine 302 corrects previous 2FB's
 // last near JMP and restores all 411 native widths.
 // Whole 82KB father remains NONEXACT.
// F1011 pinned Japanese original 004AC040 game action302.
case 0x302: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        fieldF08=g_OptionsModeAt006714D0+2;
    }
    if ((animationStage)<13 && y>FloatConstants::Zero) {
        velocityY=velocityY-field05C;
        if (velocityY<FloatConstants::One)
            velocityY=1.0f;
    }
    if ((animationStage)>12 && y>FloatConstants::Zero) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(15);
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(
            RecordedRange(0,60)+180-g_OptionsModeAt006714D0*20);
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityY=13.5f;
        field05C=0.5f;
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(5);
        if (g_OptionsModeAt006714D0==0) {
            for (int shot=0;shot<10;++shot) {
                field314=float(shot*36);
                field318=4.0f;
                SpawnBattleEffect(0x389,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_OptionsModeAt006714D0==1) {
            for (int shot=0;shot<12;++shot) {
                field314=float(shot*30);
                field318=4.0f;
                SpawnBattleEffect(0x389,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_OptionsModeAt006714D0==2) {
            for (int shot=0;shot<15;++shot) {
                field314=float(shot*24);
                field318=4.0f;
                SpawnBattleEffect(0x389,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
        if (g_OptionsModeAt006714D0==3) {
            for (int shot=0;shot<20;++shot) {
                field314=float(shot*18);
                field318=4.0f;
                SpawnBattleEffect(0x389,
                    x -
                        float((facing)*16),
                    (*(&y))+g_F972_YAt0065836C,
                    facing,1);
            }
        }
    }
    break;
}
