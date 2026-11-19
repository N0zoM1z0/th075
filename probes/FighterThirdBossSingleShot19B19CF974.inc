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
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>5 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PrepareActionAt453D40(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4-30);
        field318=15.0f;
        SpawnFloatXYAt453A70(0x326,
            float((facing)*49)+(x),
            (*(&y))+g_F974_ShotYAt00659294,
            facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    break;
}
// F974 authentic original Japanese 004AC040 action 0x19C, one shot.
case 0x19C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)>4 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        PrepareActionAt453D40(0);
        UpdateGaugeTimer(0x28);
        field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*4+30);
        field318=15.0f;
        SpawnFloatXYAt453A70(0x326,
            float((facing)*97)+(x),
            (*(&y))+g_F974_ShotYAt00659498,
            facing,1);
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    break;
}
