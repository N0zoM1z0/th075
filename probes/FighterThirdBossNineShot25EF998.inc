// F998 native Japanese TH075 original 004AC040 game state25E.
 // Physical original 004BA229..004BA59B 882 CODEB/236x86,
 // 24 genuine external PE targets. Stage0 float motion scaled
 // by 00657F74, native stage4 nine original sprite0x342
 // RAW 32-bit X / floating Y + native 006590AC shots;
 // fixed angles -28..28 by seven. Original instruction mnemonics
 // and widths match, 153 GPR roles still differ in PARTIAL father.
 // Genuine added state regresses following 25F/260/261/262 native
 // GPR phase from 0/0/0/0 to 73/73/65/65, but no x86 width debt.
// F998 true original Japanese game fighter 004AC040 action25E
case 0x25E: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        scriptCounterF00=0;
        scriptCounterF02=0;
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
    }
    if ((animationStage)>4)
        velocityY=velocityY-field05C;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=-3.0f;
        velocityY=9.0f;
        field05C=0.7f;
        PlaySound(0);
        UpdateGaugeTimer(0xFA);
        field314=-28.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=-21.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=-14.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=-7.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=0.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=7.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=14.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=21.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
        field314=28.0f;
        field318=10.0f;
        SpawnBattleEffect(0x342,x,
            (*(&y))+g_F970_YAt006590AC,
            facing,1);
    }
    break;
}
