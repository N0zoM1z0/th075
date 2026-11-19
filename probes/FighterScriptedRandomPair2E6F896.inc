// F896 original 0x2E6: 374B/102 native x86, true random-action cascade.
// Start action 0x2E5 iff random F00<30 and occupied; stage3 sprite38E.
// No fake source locals; entire original 46755B father NONEXACT.
case 0x2E6: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        field080=1;
    }
    velocityX=(velocityX)-g_F893FloatFallAt00657478;
    if ((velocityX)<g_ThresholdAt0065782C)
        velocityX=0.0f;
    if (AdvanceNestedFrame()==(field070)) {
        reinterpret_cast<signed short&>(scriptCounterF00)=RandomBoundaryAt455580(0,100);
        if (field07C==0) {
            SetNativeActionAt40FAC0(0);
            aiCardTimer=RandomBoundaryAt455580(60,120);
            return;
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<30) {
            SetNativeActionAt40FAC0(0x2E5);
            return;
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<60) {
            SetNativeActionAt40FAC0(0x2E7);
            return;
        }
        SetNativeActionAt40FAC0(0x2E8);
        return;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=15.0f;
        PlaySound(7);
        SpawnWithFloatAt453A70(0x38E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
    }
    return;
}
