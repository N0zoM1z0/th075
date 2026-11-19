// F968 original Japanese TH075 004AC040 actions 190 and 191.
 // Each complete original state: 597B/147 x86/11 native PE fields.
 // Normal source emits 561B/147x86, all ordered original mnemonics.
 // Each has TWELVE incorrect 6B-versus-3B x87 stack temp widths
 // (original EBP-0xA8..-0xD4, source much shallower) and 94
 // true GPR-role mismatches: original 82KB father NONEXACT.
 // Genuine three source projectile calls PER original state,
 // no compiled loop unrolling, original-byte grafts or filler locals.
// F968 natural original Japanese 004AC040 action 0x190, 597 B 147 native x86.
case 0x190: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>5 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-8);
        field318=7.0f;
        SpawnBattleEffect(0x320,
           float((facing)*49)+(x),
           (*(&y))+g_F968_RoundY190At00659294,
           facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-4);
        field318=7.0f;
        SpawnBattleEffect(0x320,
           float((facing)*49)+(x),
           (*(&y))+g_F968_RoundY190At00659294,
           facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-12);
        field318=7.0f;
        SpawnBattleEffect(0x320,
           float((facing)*49)+(x),
           (*(&y))+g_F968_RoundY190At00659294,
           facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    break;
}
// F968 natural original Japanese 004AC040 action 0x191, 597 B 147 native x86.
case 0x191: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>4 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4+30);
        field318=7.0f;
        SpawnBattleEffect(0x320,
           float((facing)*97)+(x),
           (*(&y))+g_F968_RoundY191At00659498,
           facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4+34);
        field318=7.0f;
        SpawnBattleEffect(0x320,
           float((facing)*97)+(x),
           (*(&y))+g_F968_RoundY191At00659498,
           facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4+26);
        field318=7.0f;
        SpawnBattleEffect(0x320,
           float((facing)*97)+(x),
           (*(&y))+g_F968_RoundY191At00659498,
           facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    break;
}
