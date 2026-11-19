// F1012 pinned Japanese TH075 original 004AC040 action303.
 // Original 004BFDAB..004C01A1: 1014 CODE B/267 x86
 // with 29 actual external PE fields. Genuine C++ cast
 // short((velocityX)/global), native borrowed opponent-X FIMUL,
 // signed-short F04+=F06 recovers all original 267
 // mnemonic and GPR roles and all widths except final
 // shared-parent tail JMP original 5B vs source2B.
 // Correct original decl-only math call 00483300
 // returns x87 ST0; original 40FB70 gets two float args.
 // Natural 303 source repairs preceding 302 final JMP width.
 // Whole original 82KB callable remains NONEXACT.
// F1012 original Japanese game fighter 004AC040 state303.
case 0x303: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
        if (RandAt455580(0,100)>50)
            reinterpret_cast<signed short&>(fieldF06)=5;
        else
            reinterpret_cast<signed short&>(fieldF06)=-5;
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
            ResetAt453E20();
            SetAuxActionAt40FB40(11);
        }
    }
    if ((animationStage)==7 || (animationStage)==8) {
        if ((animationFrame)==0) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            if ((reinterpret_cast<signed short&>(scriptCounterF00))<g_F1004_ModeAt006714D0*5+10) {
                PrepareActionAt453D40(0);
                reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
                reinterpret_cast<signed short&>(fieldF08)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
                field314=float(fieldF04);
                field318=10.0f;
                SetAngleAt40FB70(float(fieldF04),100.0f);
                SpawnFloatXYAt453A70(0x388,
                    float(facing)*(velocityX)+(x),
                    (*(&y))+g_F1012_ArcYAt006591EC-velocityY,
                    facing,1);
                velocityX=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
                velocityY=float(reinterpret_cast<signed short&>(fieldF08))*g_F747_BounceYAt00658044;
                fieldF04+=reinterpret_cast<signed short&>(fieldF06);
            }
        }
    }
    if (GetNativeActionAt40FA30()==(field070)) {
        SetNativeActionAt40FAC0(0);
        aiCardTimer=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=6.5f;
        field05C=0.25f;
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        fieldF04=static_cast<short>(
            F1012_AngleAt00483300(
                -((opponent->y)+
                    g_ContactProjectionAt00657888-y+
                    g_F1012_ArcYAt006591EC),
                (opponent->x -
                    x) *
                    (facing))/
                g_F1012_AngleDivisorAt00657828);
    }
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<25)
        SetAuxActionAt40FB40(7);
    break;
}
