// F1018 actual Japanese TH075 original 004AC040 state2BF.
 // Native 004BB831..004BC0A8 2167B/616 x86 with 65
 // genuine PE targets. Five native stages15/17/19/21/23
 // launch each THREE real sprites: 0x322+bool,
 // fixed0x340, and 0x341 signed-facing*640
 // FILD/FSUBR X and original Y-global0065784C
 // minus native Rand(0,400). Stage4 0x74,
 // stage13 real 0.9f Y speed, shot animation
 // only AFTER the three native calls. All native
 // positional mnemonic/width/GPR align. Previous
 // 2BE 125 GPR role debt persists, whole NONEXACT.
// F1018 real original Japanese actor 004AC040 2BF
case 0x2BF: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        ResetAt453E20();
        field080=99;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)>23) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<34) {
            SetAuxActionAt40FB40(34);
            ResetAt453E20();
            y=0.0f;
            break;
        }
    }
    if ((animationFrame)==0)
        field07C=0;
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==4 && (animationFrame)==0) {
        ApplyAt453E80(40);
        PrepareActionAt453D60(0x17);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x74,
            float((facing)*30)+(x),
            (*(&y))+g_F1017_StartYAt00658268,
            facing,1);
    }
    if ((animationStage)==13 && (animationFrame)==0) {
        PrepareActionAt453D40(7);
        velocityX=0.5f;
        velocityY=0.9f;
        field05C=0.5f;
        field084=20;
    }
    if ((animationStage)==15 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x340,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*640),
            ((*(&y))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            facing,1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if ((animationStage)==17 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x340,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*640),
            ((*(&y))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            facing,1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if ((animationStage)==19 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x340,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*640),
            ((*(&y))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            facing,1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if ((animationStage)==21 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x340,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*640),
            ((*(&y))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            facing,1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if ((animationStage)==23 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x340,
            float((facing)*60)+(x),
            (*(&y))+g_F1017_VolleyYAt0065908C,
            facing,1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((facing)*640),
            ((*(&y))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            facing,1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<10) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            SetAuxActionAt40FB40(15);
        }
    }
    if ((animationStage)==34 && (animationFrame)==0)
        SetAuxActionAt40FB40(32);
    break;
}
