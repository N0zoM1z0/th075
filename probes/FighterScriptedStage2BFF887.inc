// F887 original 2BF true native 473B/138-x86, two actual float->short FTOL calls.
// Stage0 short+80 0x63 THEN 1; stage2 sprites74/33D, stage10 Prepare7 and stage11 10f.
// Entire original fighter stays nonexact; no internal callable code credit.
// F886 actual original native 2BE 461B/136 x86/15 physical PE fields.
// Two true F32-to-short casts generate native __ftol2 original PE call 6406AC.
// Sprite33C needs actual RAW integer Y: floating formal adds nonnative FILD/FSTP.
// Whole original game fighter NONEXACT; no split-case acceptance.
case 0x2BF: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=0;
        field080=0x63;
        field080=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationFrame)==0)
        field07C=0;
    if ((animationStage)==2 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x74,
            x-
                float((facing)*64),
            (*(&y))+g_F884Stage5YAt00659470,
            (facing),1);
        scriptCounterF00=static_cast<signed short>(x);
        scriptCounterF02=static_cast<signed short>(y);
        Fighter::SpawnTrackedEffect(0x33D,x,y,
            (facing),1,0,1);
    }
    if ((animationStage)==10 && (animationFrame)==0) {
        UpdateGaugeTimer(0x1F4);
        PlaySound(7);
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        SetCameraShake(10.0f);
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    return;
}
