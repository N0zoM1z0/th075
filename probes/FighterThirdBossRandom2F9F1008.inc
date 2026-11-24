// F1008 original Japanese 004AC040 state 2F9.
// Entry initializes F00/F02/F04/F06, field07C and field080, then calls
// native 00453E20 to clear velocityX, velocityY, field058 and field05C.
// Stages 9/10 emit mode-gated random 38B/38A effects; stage 5 delays three
// times before opponent transform, then stages 11/13 repeat at counters 9/11.
// F1008 true original Japanese 004AC040 case 2F9
case 0x2F9: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=static_cast<short>(RecordedRange(0,3));
        fieldF06=static_cast<short>(RecordedRange(0,100));
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if ((animationFrame)==0 && ((animationStage)==9 || (animationStage)==10)) {
        SpawnBattleEffect(0x38B,
            (x)+g_F1008_CenterXAt006593D0
                - float(RecordedRange(0,480)),
            float(RecordedRange(0,200)+((fieldF06)>50)*200),
            facing,1);
        if (g_OptionsModeAt006714D0>0)
            SpawnBattleEffect(0x38B,
                (x)+g_F1008_AlternateXAt00658370
                    - float(RecordedRange(0,560)),
                float(RecordedRange(0,250)+((fieldF06)>50)*250),
                facing,1);
        if ((animationStage)==9 && (animationFrame)==0 && g_OptionsModeAt006714D0>1)
            Fighter::SpawnTrackedEffect(0x38A,
                (x)+g_F1008_CenterXAt006593D0
                    - float(RecordedRange(0,480)),
                float(RecordedRange(0,200)+((fieldF06)>50)*200),
                facing,1,0,1);
        if ((animationStage)==10 && (animationFrame)==0 && g_OptionsModeAt006714D0>2)
            Fighter::SpawnTrackedEffect(0x38A,
                (x)+g_F1008_AlternateXAt00658370
                    - float(RecordedRange(0,560)),
                float(RecordedRange(0,250)+((fieldF06)>50)*250),
                facing,1,0,1);
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(180-g_OptionsModeAt006714D0*20);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        if ((scriptCounterF02)<3) {
            ++scriptCounterF02;
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
        if ((scriptCounterF00)<10) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        } else {
            fieldF10=0;
            opponent->field010=0;
            scriptCounterF00=0;
        }
    }
    if ((animationStage)==13 && (animationFrame)==0 && (scriptCounterF00)<10) {
        ++scriptCounterF00;
        ResetSecondaryCounter(11);
    }
    break;
}
