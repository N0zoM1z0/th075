// F971: independently read original Japanese TH075 004AC040 five-shot
// actions 196/197/198, each complete internal 507B/146 native x86
// and FIFTEEN true original typed PE call/global reference fields.
// Each emits the exact native positional mnemonic/width sequence but
// 77 original GPR roles differ in the still PARTIAL 82KB father.
// Preserve original per-shot facing multipliers and global Y offsets.
// Neither case nor father is credited as a complete original game function.
// F971 original 004AC040 native 0x196 is five real projectile calls.
case 0x196: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
            }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(0);
        field314=0.0f;
        field318=20.0f;
        SpawnBattleEffect(0x328,
            float((facing)*39)+(x),
            (*(&y))+g_F971_YAt00659494,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*44)+(x),
            (*(&y))+g_F971_YAt00659490,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*49)+(x),
            (*(&y))+g_F971_YAt00659294,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*54)+(x),
            (*(&y))+g_F971_YAt0065948C,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*59)+(x),
            (*(&y))+GeometryConstants::EightySix,
            facing,1);
        UpdateGaugeTimer(0x96);
    }
    break;
}
// F971 original 004AC040 native 0x197 is five real projectile calls.
case 0x197: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
            }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(0);
        field314=25.0f;
        field318=20.0f;
        SpawnBattleEffect(0x328,
            float((facing)*85)+(x),
            (*(&y))+g_F971_YAt00659484,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*91)+(x),
            (*(&y))+g_F971_YAt00659480,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*97)+(x),
            (*(&y))+g_F971_YAt00659498,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*103)+(x),
            (*(&y))+g_F971_YAt0065947C,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*109)+(x),
            (*(&y))+g_F971_YAt00659478,
            facing,1);
        UpdateGaugeTimer(0x96);
    }
    break;
}
// F971 original 004AC040 native 0x198 is five real projectile calls.
case 0x198: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
            }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(2);
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(0);
        field314=0.0f;
        field318=20.0f;
        SpawnBattleEffect(0x328,
            float((facing)*92)+(x),
            (*(&y))+GeometryConstants::SeventyFive,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*98)+(x),
            (*(&y))+GeometryConstants::Sixty,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*104)+(x),
            (*(&y))+GeometryConstants::FortyFive,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*110)+(x),
            (*(&y))+GeometryConstants::Thirty,
            facing,1);
        SpawnBattleEffect(0x328,
            float((facing)*116)+(x),
            (*(&y))+GeometryConstants::Fifteen,
            facing,1);
        UpdateGaugeTimer(0x96);
    }
    break;
}
