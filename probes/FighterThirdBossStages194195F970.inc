// F970 original Japanese TH075 fighter 004AC040 real actions 194/195.
 // Each original physical internal case is 644 B/168 x86, 11 real PE
 // external fields. Natural complete-partial-father VC7.1 source emits
 // matching original 168 mnemonics/widths but 118 wrong GPR roles each.
 // Real three-shot angles for 194 use -8/-4/-12; for 195 -45/-41/-49.
 // Actor raw X bit-pattern passes through as integer, genuine float Y
 // adds original global 006590AC, and stage5 movement is X=-6,Yv=9.
 // Original whole 82KB fighter and EBP temp owners still NONEXACT.
// Native original Japanese TH075 fighter 004AC040 stage 0x194, 644B/168x86.
case 0x194: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>4 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PrepareActionAt453D40(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-8);
        field318=7.0f;
        SpawnWithFloatAt453A70(0x320,reinterpret_cast<int&>(x),
             (*(&y))+g_F970_YAt006590AC,
             facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-4);
        field318=7.0f;
        SpawnWithFloatAt453A70(0x320,reinterpret_cast<int&>(x),
             (*(&y))+g_F970_YAt006590AC,
             facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-12);
        field318=7.0f;
        SpawnWithFloatAt453A70(0x320,reinterpret_cast<int&>(x),
             (*(&y))+g_F970_YAt006590AC,
             facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    velocityY=velocityY-field05C;
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==4 && (animationFrame)==0)
        SpawnDirectedAt453A70(0x335,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1);
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=-6.0f;
        velocityY=9.0f;
        field05C=0.7f;
    }
    break;
}
// Native original Japanese TH075 fighter 004AC040 stage 0x195, 644B/168x86.
case 0x195: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>4 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PrepareActionAt453D40(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-45);
        field318=7.0f;
        SpawnWithFloatAt453A70(0x320,reinterpret_cast<int&>(x),
             (*(&y))+g_F970_YAt006590AC,
             facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-41);
        field318=7.0f;
        SpawnWithFloatAt453A70(0x320,reinterpret_cast<int&>(x),
             (*(&y))+g_F970_YAt006590AC,
             facing,1);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-49);
        field318=7.0f;
        SpawnWithFloatAt453A70(0x320,reinterpret_cast<int&>(x),
             (*(&y))+g_F970_YAt006590AC,
             facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    velocityY=velocityY-field05C;
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==4 && (animationFrame)==0)
        SpawnDirectedAt453A70(0x335,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1);
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=-6.0f;
        velocityY=9.0f;
        field05C=0.7f;
    }
    break;
}
