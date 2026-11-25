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
        velocityX=(velocityX)*FloatConstants::Quarter;
        velocityY=(velocityY)*FloatConstants::Quarter;
        collisionResult=1;
    }
    if (y+velocityY<=FloatConstants::Zero) {
        y=0.0f;
        ClearMotionFields();
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
            (*(&y))+GeometryConstants::HundredThirtySix,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*81)+(x),
            (*(&y))+g_F972_YAt00659474,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*86)+(x),
            (*(&y))+GeometryConstants::HundredSeven,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*91)+(x),
            (*(&y))+g_EffectOffsetNinetyTwo,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*96)+(x),
            (*(&y))+GeometryConstants::SeventySeven,
            facing,1);
        UpdateGaugeTimer(0x96);
    }
    break;
}
// F972 original Japanese 004AC040 action 0x19A, five real native shot calls.
case 0x19A: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=(velocityX)*FloatConstants::Quarter;
        velocityY=(velocityY)*FloatConstants::Quarter;
        collisionResult=1;
    }
    if (y+velocityY<=FloatConstants::Zero) {
        y=0.0f;
        ClearMotionFields();
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
            (*(&y))+GeometryConstants::SeventySeven,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*92)+(x),
            (*(&y))+GeometryConstants::SixtySeven,
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
