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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
        field07C=0;
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=99;
    }
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<22)
        velocityY=velocityY-g_F747_BounceYAt00658044;
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>23) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<34) {
            SetAuxActionAt40FB40(34);
            ResetAt453E20();
            y=0.0f;
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=0;
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(RandAt455580(60,120));
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PrepareActionAt453D40(7);
        velocityX=float(RandAt455580(0,6)-3);
        velocityY=1.5f;
        field05C=0.5f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-70);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==17 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-50);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==19 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-50);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==21 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-50);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==23 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-50);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
        if ((reinterpret_cast<signed short&>(fieldF04))<g_F1004_ModeAt006714D0*2+8) {
            ++reinterpret_cast<signed short&>(fieldF04);
            SetAuxActionAt40FB40(15);
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==34 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(32);
    break;
}

// F1019 original Japanese TH075 native state0x2F0.
case 0x2F0: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
        field07C=0;
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=99;
    }
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<22)
        velocityY=velocityY-g_F1019_FallAt00658354;
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>23) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<34) {
            SetAuxActionAt40FB40(34);
            ResetAt453E20();
            y=0.0f;
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=0;
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(RandAt455580(60,120));
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PrepareActionAt453D40(7);
        velocityX=float(RandAt455580(0,6)-3);
        velocityY=3.5f;
        field05C=0.5f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-70);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==17 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-70);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==19 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-70);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==21 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-70);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==23 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        field314=float(RandAt455580(0,100)-70);
        field318=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(reinterpret_cast<int&>(field314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                reinterpret_cast<const float&>(velocityX))*
                (facing))+(x),
            ((*(&y))+g_F1019_VolleyYAt0065908C)-velocityY,
            facing,1);
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
        if ((reinterpret_cast<signed short&>(fieldF04))<g_F1004_ModeAt006714D0*2+8) {
            ++reinterpret_cast<signed short&>(fieldF04);
            SetAuxActionAt40FB40(15);
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==34 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(32);
    break;
}
