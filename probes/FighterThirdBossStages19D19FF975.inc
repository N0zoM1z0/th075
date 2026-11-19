// F975 native Japanese TH075 original 004AC040 action19D/E/F.
 // 19D=400B/97x86/7 real PE fields; 19E=475B/128x86/12 PE;
 // 19F=478B/128x86/12 PE. Ordinary normal VC7.1 source reproduces
 // all 353 true native mnemonic and width positions, with 65/84/84
 // original GPR role differences. Original 19D has FIADD integer Y
 // and one native 0x326 shot; original 19E/F scale X/Y motion and
 // use genuine signed-short negative angle grammar (19E 0−4*F02,
 // 19F −45−4*F02), keeping real native x87 word conversions.
 // This is ONLY internal game state source in NONEXACT 82KB father.
// F975 true original Japanese 004AC040 19D stage, 400B/97 native x86.
case 0x19D: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>5 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4+55);
        field318=15.0f;
        SpawnBattleEffect(0x326,
            float((47-(reinterpret_cast<signed short&>(scriptCounterF02))*10)*(facing))+(x),
            (*(&y))+g_F969_RoundY192At00658264+(reinterpret_cast<signed short&>(scriptCounterF02))*20,
            facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(2);
    break;
}
// F975 true original Japanese 004AC040 19E, float-scaled single native shot.
case 0x19E: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
    }
    if ((animationStage)>4 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float(0-(reinterpret_cast<signed short&>(scriptCounterF02))*4);
        field318=15.0f;
        SpawnBattleEffect(0x326,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (y+velocityY<=g_ThresholdAt0065782C) {
        y=0.0f;
        ClearMotionFields();
        ResetPrimaryCounters(0xA);
        break;
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0)
        SpawnBattleEffect(0x335,x,y,
            facing,1);
    break;
}
// F975 true original Japanese 004AC040 19E, float-scaled single native shot.
case 0x19F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
    }
    if ((animationStage)>4 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float(-45-(reinterpret_cast<signed short&>(scriptCounterF02))*4);
        field318=15.0f;
        SpawnBattleEffect(0x326,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (y+velocityY<=g_ThresholdAt0065782C) {
        y=0.0f;
        ClearMotionFields();
        ResetPrimaryCounters(0xA);
        break;
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0)
        SpawnBattleEffect(0x335,x,y,
            facing,1);
    break;
}
