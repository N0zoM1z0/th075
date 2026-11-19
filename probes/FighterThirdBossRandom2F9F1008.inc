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
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=static_cast<short>(RecordedRange(0,3));
        reinterpret_cast<signed short&>(fieldF06)=static_cast<short>(RecordedRange(0,100));
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if ((animationFrame)==0 && ((animationStage)==9 || (animationStage)==10)) {
        SpawnBattleEffect(0x38B,
            (x)+g_F1008_CenterXAt006593D0
                - float(RecordedRange(0,480)),
            float(RecordedRange(0,200)+((reinterpret_cast<signed short&>(fieldF06))>50)*200),
            facing,1);
        if (g_F1004_ModeAt006714D0>0)
            SpawnBattleEffect(0x38B,
                (x)+g_F1008_AlternateXAt00658370
                    - float(RecordedRange(0,560)),
                float(RecordedRange(0,250)+((reinterpret_cast<signed short&>(fieldF06))>50)*250),
                facing,1);
        if ((animationStage)==9 && (animationFrame)==0 && g_F1004_ModeAt006714D0>1)
            Fighter::SpawnTrackedEffect(0x38A,
                (x)+g_F1008_CenterXAt006593D0
                    - float(RecordedRange(0,480)),
                float(RecordedRange(0,200)+((reinterpret_cast<signed short&>(fieldF06))>50)*200),
                facing,1,0,1);
        if ((animationStage)==10 && (animationFrame)==0 && g_F1004_ModeAt006714D0>2)
            Fighter::SpawnTrackedEffect(0x38A,
                (x)+g_F1008_AlternateXAt00658370
                    - float(RecordedRange(0,560)),
                float(RecordedRange(0,250)+((reinterpret_cast<signed short&>(fieldF06))>50)*250),
                facing,1,0,1);
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(180-g_F1004_ModeAt006714D0*20);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        if ((reinterpret_cast<signed short&>(scriptCounterF02))<3) {
            ++reinterpret_cast<signed short&>(scriptCounterF02);
            ResetSecondaryCounter(3);
            break;
        }
        PlaySound(9);
        SetNonnegativeWord(75);
        PlaySharedSound(23);
        Fighter::SpawnTrackedEffect(0x330,640.0f,320.0f,1,2,0,1);
        fieldF10=1;
        opponent->ResetTransform(0.0f,0.0f,0.0f);
        opponent->field010=0x82;
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<10) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            ResetSecondaryCounter(9);
        } else {
            fieldF10=0;
            opponent->field010=0;
            reinterpret_cast<signed short&>(scriptCounterF00)=0;
        }
    }
    if ((animationStage)==13 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(11);
    }
    break;
}
