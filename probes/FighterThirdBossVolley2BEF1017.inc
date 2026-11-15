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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=99;
    }
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
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ApplyAt453E80(40);
        PrepareActionAt453D60(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x73,
            float((facing)*30)+(x),
            (*(&y))+g_F1017_StartYAt00658268,
            facing,1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PrepareActionAt453D40(7);
        velocityX=0.5f;
        velocityY=1.0f;
        field05C=0.5f;
        reinterpret_cast<signed short&>(field084)=10;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==17 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==19 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==21 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PrepareActionAt453D40(7);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==23 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x33F,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        PrepareActionAt453D40(7);
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<6) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            SetAuxActionAt40FB40(15);
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==34 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(32);
    break;
}
