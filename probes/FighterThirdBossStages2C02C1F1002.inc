// F1002 pinned Japanese TH075 original 004AC040 2C0 and 2C1.
 // Real original 2C0=498B/135x86/14 external PE fields;
 // 2C1=522B/141x86/14 PE fields. True 453B50 mixed raw-X
 // float-Y argument ABI and later fixed 640/320 screen effect.
 // Real 2C1 stage>=5 sets F0C=180; distinct F02<4,
 // initial0x32F, fixed0x32E; original 2C0 F02<1,
 // initial0x332, fixed0x330; native ordered 453E80,
 // 453D40, 453D60 calls are different in each.
 // Both entire source cases compile with 0 wrong original
 // mnemonic/width AND GPR roles, but whole 82KB NONEXACT.
// F1002 original Japanese 004AC040 action 2C0
case 0x2C0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        SpawnSevenRawXFloatYAt453B50(0x332,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            1,1,0,1);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        if ((reinterpret_cast<signed short&>(scriptCounterF02))<1) {
            ++reinterpret_cast<signed short&>(scriptCounterF02);
            ResetSecondaryCounter(3);
            break;
        }
        ApplyAt453E80(0x64);
        PlaySharedSound(0x17);
        PlaySound(9);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x73,
            x
                - float((facing)*18),
            (*(&y))+g_F972_YAt00659284,
            facing,1);
        Fighter::SpawnTrackedEffect(0x330,640.0f,320.0f,1,2,0,1);
        fieldF10=spirit;
        fieldF12=1;
    }
    if ((animationStage)==11 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<4) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(9);
    }
    break;
}
// F1002 original Japanese 004AC040 action 2C1
case 0x2C1: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if ((animationStage)>=5)
        fieldF0C=180;
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        SpawnSevenRawXFloatYAt453B50(0x32F,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            1,1,0,1);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        if ((reinterpret_cast<signed short&>(scriptCounterF02))<4) {
            ++reinterpret_cast<signed short&>(scriptCounterF02);
            ResetSecondaryCounter(3);
            break;
        }
        ApplyAt453E80(0x28);
        PlaySound(0xA);
        PlaySharedSound(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x73,
            x
                - float((facing)*18),
            (*(&y))+g_F972_YAt00659284,
            facing,1);
        Fighter::SpawnTrackedEffect(0x32E,640.0f,320.0f,1,2,0,1);
        fieldF0C=spirit;
        fieldF0E=0;
    }
    if ((animationStage)==11 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<4) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(9);
    }
    break;
}
