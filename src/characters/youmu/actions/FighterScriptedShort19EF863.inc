// F863 actual original 0x19E: 122 native B/35 x86/three PE calls.
// Full original fighter switch interior, NOT independent exact CODE.
case 0x19E: {
    if ((animationStage)==0 && (animationFrame)==0) {
        remainingHits=1;
        collisionResult=0;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0)
        collisionResult=1;
    return;
}
