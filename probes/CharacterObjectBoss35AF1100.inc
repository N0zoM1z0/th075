// F1100 authentic Japanese original action 0x35A at 00515EF2..00515F65,
// 115 native CODE B /27 x86, inside ONE nonexact original 81KB boss.
case 0x35A: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.5f;
        scaleY=1.5f;
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
