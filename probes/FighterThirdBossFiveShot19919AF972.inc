// F972 original Japanese 004AC040 real action199/19A, each
// native physical 593B/170x86 with 19 true external PE/global fields.
// Full-source tested ordinary typed velocityY owner access restores
// native ordered x87 FLD member, FMUL physical global 00657F74.
// Historical velocityY=velocityY*global creates two wrong original widths,
// despite identical total CODE B! No cropped exact or byte patching.
// With correct field access each state still has 91 wrong GPR roles.
// The entire original 82KB game fighter remains NONEXACT.
// F972 original Japanese 004AC040 action 0x199, five real native shot calls.
case 0x199: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
        field07C=1;
    }
    if (y+velocityY<=g_ThresholdAt0065782C) {
        y=0.0f;
        ResetPrimaryCounters(0xA);
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(0);
        field314=0.0f;
        field318=20.0f;
        SpawnBattleEffect(0x328,
            float((facing)*76)+(x),
            (*(&y))+g_F972_YAt0065836C,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*81)+(x),
            (*(&y))+g_F972_YAt00659474,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*86)+(x),
            (*(&y))+g_F972_YAt00657860,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*91)+(x),
            (*(&y))+g_F972_YAt00659284,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*96)+(x),
            (*(&y))+g_F972_YAt00659470,
            facing,1);
        UpdateGaugeTimer(0x96);
    }
    break;
}
// F972 original Japanese 004AC040 action 0x19A, five real native shot calls.
case 0x19A: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
        field07C=1;
    }
    if (y+velocityY<=g_ThresholdAt0065782C) {
        y=0.0f;
        ResetPrimaryCounters(0xA);
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(0);
        field314=-20.0f;
        field318=20.0f;
        SpawnBattleEffect(0x328,
            float((facing)*98)+(x),
            (*(&y))+g_F972_YAt00659470,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*92)+(x),
            (*(&y))+g_F972_YAt00658364,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*86)+(x),
            (*(&y))+g_F972_YAt0065946C,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*80)+(x),
            (*(&y))+g_F972_YAt00659468,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*74)+(x),
            (*(&y))+g_F972_YAt00659464,
            facing,1);
        UpdateGaugeTimer(0x96);
    }
    break;
}
