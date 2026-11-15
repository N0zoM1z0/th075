// F1104: Japanese original game action 0x35D at 00516517..00516646,
// genuine 303 native CODE B /67 x86 inside ONE still-NONEXACT boss.
case 0x35D: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0)
        reinterpret_cast<signed short&>(field0D8)=0;
    if (F1024_PHASE(this).stageAt62==1 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->StartAnimationAt0046D000(20);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x330,
            (*(&F1037_POSITION(this).xPosition))+g_F1057_YOffsetAt00657888-
                float(RandomBoundaryAt00455580(0,200)),
            0.0f,facing,1);
        ++reinterpret_cast<signed short&>(field0D8);
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        if (reinterpret_cast<signed short&>(field0D8)<5)
            SetAuxActionAt0040FB40(1);
        else
            NativeParentExpiredAt0045B830();
    }
    return;
}
