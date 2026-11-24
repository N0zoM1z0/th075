// F1017 SHA-pinned Japanese original 004AC040 state 2BE:
 // real 004BB1EA..004BB831, 1607 CODE B/471 native x86,
 // 50 genuine physical PE call and global fields.
 // Stage4 signed-facing*30 FILD/FADD initial sprite0x73,
 // native Y global00658268; stage15/17/19/21/23 five
 // distinct original sprite pair 0x321+randomBoolean
 // and0x33F using Y global0065908C, signed facing*60.
 // Genuine stage13 velocity and hit counter, stage23
 // F00<6 auxiliary15 and stage34 auxiliary32.
 // Entire original-shaped PARTIAL source all native mnem
 // and width roles, 125 wrong GPR roles. Whole 82KB NONEXACT.
// F1017 real original fighter action 2BE.
case 0x2BE: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if (y>FloatConstants::Zero && (animationStage)>23) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero && (animationStage)<34) {
            ResetSecondaryCounter(34);
            ClearMotionFields();
            y=0.0f;
            break;
        }
    }
    if ((animationFrame)==0)
        field07C=0;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0) {
        SetNonnegativeWord(40);
        PlaySharedSound(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAuxEffect(0x73,
            float((facing)*30)+(x),
            (*(&y))+g_F1017_StartYAt00658268,
            facing,1);
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        PlaySound(7);
        velocityX=0.5f;
        velocityY=1.0f;
        field05C=0.5f;
        field084=10;
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        UpdateGaugeTimer(0xC);
        SpawnBattleEffect(0x321+(RecordedRange(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnBattleEffect(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PlaySound(7);
    }
    if ((animationStage)==17 && (animationFrame)==0) {
        UpdateGaugeTimer(0xC);
        SpawnBattleEffect(0x321+(RecordedRange(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnBattleEffect(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PlaySound(7);
    }
    if ((animationStage)==19 && (animationFrame)==0) {
        UpdateGaugeTimer(0xC);
        SpawnBattleEffect(0x321+(RecordedRange(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnBattleEffect(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PlaySound(7);
    }
    if ((animationStage)==21 && (animationFrame)==0) {
        UpdateGaugeTimer(0xC);
        SpawnBattleEffect(0x321+(RecordedRange(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnBattleEffect(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PlaySound(7);
    }
    if ((animationStage)==23 && (animationFrame)==0) {
        UpdateGaugeTimer(0xC);
        SpawnBattleEffect(0x321+(RecordedRange(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnBattleEffect(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PlaySound(7);
        if ((scriptCounterF00)<6) {
            ++scriptCounterF00;
            ResetSecondaryCounter(15);
        }
    }
    if ((animationStage)==34 && (animationFrame)==0)
        ResetSecondaryCounter(32);
    break;
}
