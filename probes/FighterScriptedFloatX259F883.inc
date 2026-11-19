// F883 native action259 PHYSICAL 206B/60x86/6 PE fields ends at action2BC.
// Numeric successor 25A is default, NOT native physical successor.
// Actual facing FILD EBP-B8 sprite34D and animation46D000(1F4).
// Complete giant remains nonexact; no internal action callable credit.
// F881 original native action258 206B/60 x86/6 genuine physical PE fields.
// Stage2 sprite340 float X from FILD signed facing*80, original raw integer Y.
// Native narrow char parameter, StartAnimation46D000(FA), Prepare5.
// Enclosing full fighter NONEXACT; no separate callable case credit.
case 0x259: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetAt453E20();
        field080=1;
        field07C=1;
        field3AC=0;
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        SpawnFloatXRawYAt453A70(0x34D,
            float((facing)*80)+(x),
            reinterpret_cast<int&>(y),(facing),1);
        UpdateGaugeTimer(0x1F4);
        PrepareActionAt453D40(5);
    }
    return;
}
