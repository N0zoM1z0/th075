// F1019 real Japanese original 004AC040 actions 2EF and 2F0.
 // Each physical PE 2229 native CODE B/573 x86/80 actual PE
 // fields. Both normal whole PARTIAL father source interiors
 // have ZERO native positional mnemonic, width and GPR errors.
 // 2EF fall global00658044 vs 2F0 global00658354,
 // stage13 vertical1.5f vs3.5f, first random angle
 // minus70 vs four following −50. Last stage23 F04
 // counter condition must be NESTED within stage23.
 // Original 0040FB70 receives raw 32-bit float angle
 // bits (one MOV and PUSH), not C++ FP FLD/FSTP.
 // Borrowed CONST actor velocity+0x50 yields original
 // FLD global00658264 / FADD actor+0x50, then FIMUL
 // signed facing, unlike mutable raw-pointer alternatives.
 // Whole original 82KB parent remains NONEXACT: one extra
 // native original-sized slot in our generated father,
 // CODE +6 B, frame0x724 vs native0x720, prior 2BE GPR
 // roles and original physical whole offsets still differ.
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
    if (AdvanceNestedFrame()==(field070)) {
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
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==17 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==19 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==21 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==23 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-50);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
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
    if (AdvanceNestedFrame()==(field070)) {
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
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==17 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==19 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==21 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(scriptCounterF00)*g_F747_BounceYAt00658044;
        velocityY=float(scriptCounterF02)*g_F747_BounceYAt00658044;
        PlaySound(7);
    }
    if ((animationStage)==23 && (animationFrame)==0) {
        scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
        scriptCounterF02=(velocityY)*g_ContactProjectionAt00657888;
        field314=float(RecordedRange(0,100)-70);
        field318=float(RecordedRange(0,10)+5);
        SetPolarVelocity(field314,100.0f);
        SpawnBattleEffect(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
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
