// F1099 authentic Japanese original action 0x359 at 00515E7F..00515EF2,
// 115 native CODE B /24 x86, inside ONE nonexact original 81KB boss.
case 0x359: {
    if (animationStage==0 && animationFrame==0) {
        field0D8=0;
        field080=1;
        field07C=0;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
