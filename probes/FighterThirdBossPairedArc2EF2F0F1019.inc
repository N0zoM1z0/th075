// F1019 original Japanese 004AC040 actions 2EF and 2F0.
// Native entry and landing both call 00453E20, clearing velocityX,
// velocityY, field058 and field05C before the stage handoff.
// 2EF uses gravity 00658044, stage-13 lift 1.5 and angles -70/-50;
// 2F0 uses gravity 00658354, stage-13 lift 3.5 and angles -70.
// The stage-23 F04 repeat guard remains nested inside the final shot.
// FUN_006406AC truncates x87 values toward zero before short stores;
// direct C++ float-to-short casts preserve that conversion.
// FUN_0040FB70 consumes the stored float angle and speed 100.
// F1019 original Japanese TH075 native state0x2EF.
case 0x2EF: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<22)
        velocityY=velocityY-g_F747_BounceYAt00658044;
    if (y>g_ThresholdAt0065782C && (animationStage)>23) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<34) {
            ResetSecondaryCounter(34);
            ClearMotionFields();
            y=0.0f;
            break;
        }
    }
    if ((animationFrame)==0)
        field07C=0;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(RecordedRange(60,120));
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        PlaySound(7);
        velocityX=float(RecordedRange(0,6)-3);
        velocityY=1.5f;
        field05C=0.5f;
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==17 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==19 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==21 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==23 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
        if ((fieldF04)<g_F1004_ModeAt006714D0*2+8) {
            ++fieldF04;
            ResetSecondaryCounter(15);
        }
    }
    if ((animationStage)==34 && (animationFrame)==0)
        ResetSecondaryCounter(32);
    break;
}

// F1019 original Japanese TH075 native state0x2F0.
case 0x2F0: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        scriptCounterF02=0;
        fieldF04=0;
        field07C=0;
        ClearMotionFields();
        field080=99;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<22)
        velocityY=velocityY-g_F1019_FallAt00658354;
    if (y>g_ThresholdAt0065782C && (animationStage)>23) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<34) {
            ResetSecondaryCounter(34);
            ClearMotionFields();
            y=0.0f;
            break;
        }
    }
    if ((animationFrame)==0)
        field07C=0;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=static_cast<short>(RecordedRange(60,120));
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        PlaySound(7);
        velocityX=float(RecordedRange(0,6)-3);
        velocityY=3.5f;
        field05C=0.5f;
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==17 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==19 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==21 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==23 && (animationFrame)==0) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                velocityX)*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
        if ((fieldF04)<g_F1004_ModeAt006714D0*2+8) {
            ++fieldF04;
            ResetSecondaryCounter(15);
        }
    }
    if ((animationStage)==34 && (animationFrame)==0)
        ResetSecondaryCounter(32);
    break;
}
