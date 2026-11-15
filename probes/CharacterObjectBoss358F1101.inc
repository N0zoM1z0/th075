// F1101: native Japanese 00515C0E..00515E7F action 0x358,
// 625 original CODE B/143 x86, within one still-NONEXACT 81KB owner.
case 0x358: {
    if (reinterpret_cast<signed short&>(owner->action)>0x31 &&
        reinterpret_cast<signed short&>(owner->action)<0x96 &&
        F1024_PHASE(this).stageAt62<0x17) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<10;++shot)
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        F1037_MOTION(this).xMotion=8.0f;
    }
    if (F1024_PHASE(this).stageAt62==1 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(2);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x359,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
    }
    if (F1037_POSITION(this).xPosition>g_F1101_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1101_LeftAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        if (reinterpret_cast<signed short&>(field0D8)<5) {
            ++reinterpret_cast<signed short&>(field0D8);
            SetAuxActionAt0040FB40(1);
        } else
            NativeParentExpiredAt0045B830();
    }
    return;
}
