// F958: consecutive real native Japanese 004AC040 stages 12C/12D.
 // 12C physically 004B1039..004B1108 (207B/59x86/6 PE fields);
 // 12D physically 004B1108..004B11E3 (219B/61x86/6 PE fields).
 // True 12C is contiguous after D2 but has NO standalone afterRET
 // DIR32 table entry: source must be verified through the real D2
 // terminal and mapped 12D successor, not a fabricated jump label.
 // Only inner source in a NONEXACT 82KB original fighter father.
// Natural native 004AC040 12C original game state, source probe.
case 0x12C: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0)
            ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D60(0x1B);
    break;
}
// Natural native 004AC040 12D original game state, source probe.
case 0x12D: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0)
            ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D60(0x1C);
    break;
}
