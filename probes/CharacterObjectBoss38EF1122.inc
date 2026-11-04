// F1122: genuine Japanese original 0x38E 0051C91E..0051CAB0,
// 402 native CODE B /91 x86 inside ONE NONEXACT 81KB parent.
case 0x38E: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(unsigned int,0x50)=SELF_FIELD(unsigned int,0xC8);
    }
    if (F1024_PHASE(this).stageAt62==1 && F1024_PHASE(this).frameAt64==0)
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x38F,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1);
    if (F1037_POSITION(this).xPosition>g_F1101_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1101_LeftAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        if (SELF_FIELD(signed short,0xD8)<int(g_F1113_DifficultyAt006714D0)*8+10) {
            ++SELF_FIELD(signed short,0xD8);
            SetAuxActionAt0040FB40(1);
        }
    }
    return;
}
