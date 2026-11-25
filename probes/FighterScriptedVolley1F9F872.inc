// F872 original game 0x1F9, whole 227B/65-x86, original physical fields.
// Stage2 motion3 float X facing*original mult, Y original global, owner+0x82.
// Complete father NONEXACT, no independent case exact CODE.
case 0x1F9: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
        field3AC=0;
    }
    if ((animationStage)==2 && collisionResult==3) {
        SpawnAuxEffect(0x32,
            float((facing)*50)+(x),
            (*(&y))+g_F872Volley1F9YAt006598BC,
            (facing),1);
        PlaySharedSound(0x14);
        opponent->hitstopFrames=0x1E;
        ResetPrimaryCounters(0x1FB);
        return;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    return;
}
