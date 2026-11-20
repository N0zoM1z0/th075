// F629: genuine complete original native action0x91 arc trajectory,
// inside a huge incomplete fighter Advance(). Game case evidence,
// not an independent original CODE function or accepted match unit.
case 0x91: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=-10.0f;
        velocityY=14.0f;
        field05C=0.5f;
        field07C=0;
    }
    if (animationStage==F629_STAGE && velocityY<g_StopThresholdAt00657480) {
        ResetSecondaryCounter(F629_EARLY);
        break;
    }
    velocityY=velocityY-field05C;
    if (velocityY+y<=g_ThresholdAt0065782C) {
        scriptCounterF00=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(F629_LATE);
    break;
}
