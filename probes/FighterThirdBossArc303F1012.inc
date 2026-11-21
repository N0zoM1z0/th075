// F1012 pinned Japanese TH075 original 004AC040 action303.
 // Original 004BFDAB..004C01A1: 1014 CODE B/267 x86
 // with 29 actual external PE fields. Native x87 nearest-even
 // conversions for projected velocity and F04 use the shared
 // SakuyaRoundFloatToShort C++ helper; opponent-X FIMUL and
 // signed-short F04+=F06 preserve the original update order.
 // mnemonic and GPR roles and all widths except final
 // shared-parent tail JMP original 5B vs source2B.
 // Correct original decl-only math call 00483300
 // returns x87 ST0; original 40FB70 gets two float args.
 // Natural 303 source repairs preceding 302 final JMP width.
 // Whole original 82KB callable remains NONEXACT.
// F1012 original Japanese game fighter 004AC040 state303.
case 0x303: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        if (RecordedRange(0,100)>50)
            fieldF06=5;
        else
            fieldF06=-5;
    }
    if ((animationStage)<9 && y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (velocityY<g_AnimationDeltaAt0065747C)
            velocityY=1.0f;
    }
    if ((animationStage)>8 && y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(11);
        }
    }
    if ((animationStage)==7 || (animationStage)==8) {
        if ((animationFrame)==0) {
            ++scriptCounterF00;
            if ((scriptCounterF00)<g_F1004_ModeAt006714D0*5+10) {
                PlaySound(0);
                scriptCounterF02=SakuyaRoundFloatToShort((velocityX)*g_ContactProjectionAt00657888);
                fieldF08=SakuyaRoundFloatToShort((velocityY)*g_ContactProjectionAt00657888);
                field314=float(fieldF04);
                field318=10.0f;
                SetPolarVelocity(float(fieldF04),100.0f);
                SpawnBattleEffect(0x388,
                    float(facing)*(velocityX)+(x),
                    (*(&y))+g_F1012_ArcYAt006591EC-velocityY,
                    facing,1);
                velocityX=float(scriptCounterF02)*g_F747_BounceYAt00658044;
                velocityY=float(fieldF08)*g_F747_BounceYAt00658044;
                fieldF04+=fieldF06;
            }
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(
            RecordedRange(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=6.5f;
        field05C=0.25f;
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        fieldF04=SakuyaRoundFloatToShort(
            F1012_AngleAt00483300(
                -((opponent->y)+
                    g_ContactProjectionAt00657888-y+
                    g_F1012_ArcYAt006591EC),
                (opponent->x -
                    x) *
                    (facing))/
                g_F1012_AngleDivisorAt00657828);
    }
    if ((animationStage)==9 && (animationFrame)==0 && (scriptCounterF00)<25)
        ResetSecondaryCounter(7);
    break;
}
