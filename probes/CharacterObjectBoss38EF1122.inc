// F1122: genuine Japanese original 0x38E 0051C91E..0051CAB0,
// 402 native CODE B /91 x86 inside ONE NONEXACT 81KB parent.
case 0x38E: {
    if (reinterpret_cast<signed short&>(owner->field3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<unsigned int&>(velocityX)=reinterpret_cast<unsigned int&>(field0C8);
    }
    if (F1024_PHASE(this).stageAt62==1 && F1024_PHASE(this).frameAt64==0)
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x38F,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
    if (F1037_POSITION(this).xPosition>g_F1101_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1101_LeftAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        if (reinterpret_cast<signed short&>(field0D8)<int(g_F1113_DifficultyAt006714D0)*8+10) {
            ++reinterpret_cast<signed short&>(field0D8);
            SetAuxActionAt0040FB40(1);
        }
    }
    return;
}
