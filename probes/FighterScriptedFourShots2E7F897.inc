// F897: original 2E7..2EA four distinct physical 555B/167-x86 cases.
// Only stage9 sprite differs (0x38B/0x38C); native FILD scratch differs
// because each truly used float projectile has an independent source case.
// Whole 46,755B original father is NONEXACT. Do not credit split game CODE.
case F897_CASE: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        field080=0x63;
        ClearMotionFields();
    }
    if ((animationStage)==3 && (animationFrame)<30) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>4) {
            SpawnAt453C80(0x3E,
                x-
                    float((facing)*65),
                (*(&y))+g_F860ShotYAt006581DC,1,1);
            reinterpret_cast<signed short&>(scriptCounterF02)=0;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RandomBoundaryAt455580(0,60)+60-
                      static_cast<int>(g_CloudOpponentAt006714D0);
        return;
    }
    if ((animationFrame)==0)
        field07C=0;
    if ((animationStage)==2 && (animationFrame)==0) {
        PlaySharedSound(0x17);
        reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<signed short>(x);
        reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<signed short>(y);
        SpawnExtraRawYAt453B50(0x33D,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1,0,1);
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        SpawnExtraRawYAt453B50(F897_SECOND_SPRITE,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1,0,1);
        PlaySound(7);
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        InitTrajectoryAt453E60(10.0f);
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    }
    return;
}
