// F974 original Japanese TH075 004AC040 single-shot 19B/19C.
 // Original each 355B/87 x86/7 genuine typed PE/global fields.
 // Authentic native source +0x314 angle, +0x318 float velocity, sprite
 // 0x326 original call; 19B facing*49 at stage>5 and angle -30;
 // 19C facing*97 at stage>4 and angle +30. Both normal VC7.1
 // sources emit native whole case mnemonic/width but 56 wrong GPR.
 // Entire original 82KB game fighter remains NONEXACT.
// F974 authentic original Japanese 004AC040 action 0x19B, one shot.
case 0x19B: {
    if ((animationStage)==0 && (animationFrame)==0) {
        collisionResult=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>5 && (scriptCounterF00)<=0 && (scriptCounterF02)<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float((scriptCounterF02)*4-30);
        field318=15.0f;
        SpawnBattleEffect(0x326,
            float((facing)*49)+(x),
            (*(&y))+GeometryConstants::HundredSixteen,
            facing,1);
        scriptCounterF00=2;
        ++scriptCounterF02;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    break;
}
// F974 authentic original Japanese 004AC040 action 0x19C, one shot.
case 0x19C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        collisionResult=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>4 && (scriptCounterF00)<=0 && (scriptCounterF02)<5) {
        PlaySound(0);
        UpdateGaugeTimer(0x28);
        field314=float((scriptCounterF02)*4+30);
        field318=15.0f;
        SpawnBattleEffect(0x326,
            float((facing)*97)+(x),
            (*(&y))+g_F974_ShotYAt00659498,
            facing,1);
        scriptCounterF00=2;
        ++scriptCounterF02;
    }
    --scriptCounterF00;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    break;
}
