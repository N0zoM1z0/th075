// F888 real original game 0x2C0 stage1, true real 453B50 sprite345.
// F10=420 guard is stage>10 for 2C0 but ONLY getter match for 2C1.
// Full 46755B giant NONEXACT, do not treat original inner case as callable CODE.
case 0x2C0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        field080=1;
        ClearMotionFields();
    }
    if ((animationStage)==1 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        PlaySound(8);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x73,x,
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
    }
    if ((animationStage)>10)
        fieldF10=0x1A4;
    if (AdvanceNestedFrame()==(field070)) {

        ResetPrimaryCounters(0);
        Fighter::SpawnTrackedEffect(0x345,x,
        (*(&y))+g_ContactProjectionAt00657888,1,1,0,1);
    }
    return;
}
