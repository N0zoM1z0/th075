// F630 actual native 105-instruction action0x91 in two special giant
// fighter C++ sources. This 27-instruction stage-one projectile path
// is absent from original regular 78-instruction F629 actors.
// A full parent Advance() remains NONEXACT; this is not a new function.
case 0x91: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=-10.0f;
        velocityY=14.0f;
        field05C=0.5f;
        field07C=0;
    }
    if (animationStage==1 && animationFrame==0 && fieldF0C==0) {
        fieldF0C=1;
        SpawnBattleEffect(F630_PROJECTILE,x,y,
            facing,F630_SIDE);
    }
    if (animationStage==F630_STAGE && velocityY<FloatConstants::Two) {
        ResetSecondaryCounter(F630_EARLY);
        break;
    }
    velocityY=velocityY-field05C;
    if (velocityY+y<=FloatConstants::Zero) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(F630_LATE);
    break;
}
