// F1117: genuine original Japanese action 0x388, PE
// 0051B89F..0051BB8B, 748 native CODE B /160 x86. One inner
// state of the still-NONEXACT 81KB CharacterObject Advance.
case 0x388: {
    if (owner->field3A0<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (field07C==6) {
        ++field080;
        field07C=0;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,60.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field080=1;
        field07C=0;
        F1037_MOTION(this).yMotion=22.5f;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(3);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x345,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
    }
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (F1024_PHASE(this).stageAt62==1) {
        rotationZ=(rotationZ)+g_F1068_ActionSpeedAt00657878;
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1051_ScaleCeilingAt0065747C;
        if (F1037_MOTION(this).yMotion<g_F1044_GroundAt0065782C)
            F1037_MOTION(this).yMotion=0.0f;
    }
    if (F1024_PHASE(this).stageAt62==2) {
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1059_ScaleRatioAt00657478;
        F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
        // Native TEST AH,0x41; JNP jumps straight INTO the hit
        // body. Otherwise, only then consult native status 0/6.
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C ||
            (field07C!=0 && field07C!=6)) {
            F1037_MOTION(this).yMotion=0.0f;
            SetAuxActionAt0040FB40(3);
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(5);
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(4);
        F1037_MOTION(this).xMotion=-10.0f;
        rotationZ=0.0f;
    }
    return;
}
