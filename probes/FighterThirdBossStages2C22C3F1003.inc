// F1003 pinned original Japanese 004AC040 fighter 2C2 and 2C3.
 // Original 2C2 515B/138x86/14 genuine typed PE targets,
 // original 2C3 522B/141x86/14 PE fields. Native source
 // recovers getter==frame unconditional sprite0x332 in branch
 // with short F12=1 and genuine BREAK/jump to shared tail.
 // 2C3 stage>5 F0C=300, true stage5 order 453E80(0x28)
 // then Prepare453D60(0x17), then Prepare453D40(0xA).
 // Both all mnemonic/width/GPR roles align under normal full
 // partial 82KB VC7.1 father source; whole giant NONEXACT.
// F1002 original Japanese 004AC040 action 2C0
case 0x2C2: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        fieldF12=1;
        Fighter::SpawnTrackedEffect(0x332,x,
            (*(&y))+g_ContactProjectionAt00657888,
            1,1,0,1);
        break;
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        if ((scriptCounterF02)<1) {
            ++scriptCounterF02;
            ResetSecondaryCounter(3);
            break;
        }
        SetNonnegativeWord(0x64);
        PlaySharedSound(0x17);
        PlaySound(9);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x74,
            x
                - float((facing)*18),
            (*(&y))+g_F972_YAt00659284,
            facing,1);
        Fighter::SpawnTrackedEffect(0x330,640.0f,320.0f,1,2,0,1);
        fieldF10=spirit;
        fieldF12=1;
    }
    if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<4) {
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
    }
    break;
}
// F1002 original Japanese 004AC040 action 2C1
case 0x2C3: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if ((animationStage)>5)
        fieldF0C=300;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        Fighter::SpawnTrackedEffect(0x32F,x,
            (*(&y))+g_ContactProjectionAt00657888,
            1,1,0,1);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        if ((scriptCounterF02)<4) {
            ++scriptCounterF02;
            ResetSecondaryCounter(3);
            break;
        }
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        PlaySound(0xA);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x74,
            x
                - float((facing)*18),
            (*(&y))+g_F972_YAt00659284,
            facing,1);
        Fighter::SpawnTrackedEffect(0x32E,640.0f,320.0f,1,2,0,1);
        fieldF0C=spirit;
        fieldF0E=0;
    }
    if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<4) {
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
    }
    break;
}
