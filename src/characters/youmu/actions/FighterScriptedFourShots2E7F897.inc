// F897: original 2E7..2EA four distinct physical 555B/167-x86 cases.
// Only stage9 sprite differs (0x38B/0x38C); native FILD scratch differs
// because each truly used float projectile has an independent source case.
// Whole 46,755B original father is NONEXACT. Do not credit split game CODE.
case F897_CASE: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        collisionResult=0;
        remainingHits=0x63;
        ClearMotionFields();
    }
    if ((animationStage)==3 && (animationFrame)<30) {
        ++scriptCounterF02;
        if ((scriptCounterF02)>4) {
            SpawnAuxEffect(0x3E,
                x-
                    float((facing)*65),
                (*(&y))+GeometryConstants::Ninety,1,1);
            scriptCounterF02=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RecordedRange(0,60)+60-
                      static_cast<int>(g_OptionsModeAt006714D0);
        return;
    }
    if ((animationFrame)==0)
        collisionResult=0;
    if ((animationStage)==2 && (animationFrame)==0) {
        PlaySharedSound(0x17);
        scriptCounterF00=(x);
        scriptCounterF02=(y);
        Fighter::SpawnTrackedEffect(0x33D,x,y,
            (facing),1,0,1);
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        Fighter::SpawnTrackedEffect(F897_SECOND_SPRITE,x,y,
            (facing),1,0,1);
        PlaySound(7);
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        SetCameraShake(10.0f);
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    return;
}
