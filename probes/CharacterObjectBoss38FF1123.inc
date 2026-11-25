// F1123: real Japanese original 0x38F 0051CAB0..0051CB4A,
// 154 native CODE B /32 x86 inside ONE NONEXACT 81KB parent.
case 0x38F: {
    if (owner->spellTimer<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        field0D8=0;
        remainingHits=1;
        collisionResult=0;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
