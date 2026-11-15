// F1008 pinned original Japanese 004AC040 2F9:
 // 1254 native CODEB /326x86 /33 real PE targets.
 // True random sprites0x38B and 7-arg sprite0x38A
 // gated by signed global mode006714D0, physical
 // two center-X globals006593D0/00658370 and
 // native F06>50 boolean offsets. Native stage5
 // opponent motion/F10, stage11/13 bounded aux.
 // Full-partial natural VC7.1 parent aligns all
 // 326 native mnemonics/width/GPR roles. Genuine
 // preceding 2F9 restores next 2FA GPR phase
 // from 113 wrong -> ZERO; whole giant NONEXACT.
// F1008 true original Japanese 004AC040 case 2F9
case 0x2F9: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=static_cast<short>(RandAt455580(0,3));
        reinterpret_cast<signed short&>(fieldF06)=static_cast<short>(RandAt455580(0,100));
        field07C=0;
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=99;
    }
    if ((reinterpret_cast<signed short&>(animationFrame))==0 && ((reinterpret_cast<signed short&>(animationStage))==9 || (reinterpret_cast<signed short&>(animationStage))==10)) {
        SpawnFloatXYAt453A70(0x38B,
            (x)+g_F1008_CenterXAt006593D0
                - float(RandAt455580(0,480)),
            float(RandAt455580(0,200)+((reinterpret_cast<signed short&>(fieldF06))>50)*200),
            facing,1);
        if (g_F1004_ModeAt006714D0>0)
            SpawnFloatXYAt453A70(0x38B,
                (x)+g_F1008_AlternateXAt00658370
                    - float(RandAt455580(0,560)),
                float(RandAt455580(0,250)+((reinterpret_cast<signed short&>(fieldF06))>50)*250),
                facing,1);
        if ((reinterpret_cast<signed short&>(animationStage))==9 && (reinterpret_cast<signed short&>(animationFrame))==0 && g_F1004_ModeAt006714D0>1)
            SpawnSevenFloatAt453B50(0x38A,
                (x)+g_F1008_CenterXAt006593D0
                    - float(RandAt455580(0,480)),
                float(RandAt455580(0,200)+((reinterpret_cast<signed short&>(fieldF06))>50)*200),
                facing,1,0,1);
        if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && g_F1004_ModeAt006714D0>2)
            SpawnSevenFloatAt453B50(0x38A,
                (x)+g_F1008_AlternateXAt00658370
                    - float(RandAt455580(0,560)),
                float(RandAt455580(0,250)+((reinterpret_cast<signed short&>(fieldF06))>50)*250),
                facing,1,0,1);
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(180-g_F1004_ModeAt006714D0*20);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((reinterpret_cast<signed short&>(scriptCounterF02))<3) {
            ++reinterpret_cast<signed short&>(scriptCounterF02);
            SetAuxActionAt40FB40(3);
            break;
        }
        PrepareActionAt453D40(9);
        ApplyAt453E80(75);
        PrepareActionAt453D60(23);
        SpawnSevenFloatAt453B50(0x330,640.0f,320.0f,1,2,0,1);
        reinterpret_cast<signed short&>(fieldF10)=1;
        reinterpret_cast<FighterSwitchF598_Boss004AC040*>(opponent)->SetMotionStateAt40FBB0(0,0.0f,0);
        opponent->field010=0x82;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<10) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            SetAuxActionAt40FB40(9);
        } else {
            reinterpret_cast<signed short&>(fieldF10)=0;
            opponent->field010=0;
            reinterpret_cast<signed short&>(scriptCounterF00)=0;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(11);
    }
    break;
}
