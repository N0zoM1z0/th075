// F1116: original Japanese action 0x387, PE 0051B5AF..0051B89F,
// 752 native CODE bytes/167 x86 within ONE still-NONEXACT 81KB boss.
case 0x387: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (reinterpret_cast<signed short&>(owner->field3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        reinterpret_cast<signed short&>(field0D8)=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=float(RandomBoundaryAt00455580(0,0x167));
        F1037_MOTION(this).xMotion=float(RandomBoundaryAt00455580(0,16)-8);
        F1037_MOTION(this).yMotion=float(RandomBoundaryAt00455580(0,6)+12);
    }
    // The native stage-zero guard jumps to ordinal 92: BOTH the
    // velocity decrement and angle nudge run on every frame.
    F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1116_YOffsetAt00659888;
    rotationZ=(rotationZ)+g_F1116_AngleOffsetAt0065786C;
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (F1024_PHASE(this).stageAt62==1) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            SetAuxActionAt0040FB40(2);
            F1037_MOTION(this).yMotion=-F1037_MOTION(this).yMotion;
            F1037_POSITION(this).yPosition=0.0f;
        }
    }
    if (F1024_PHASE(this).stageAt62==2) {
        if (color[0]>15)
            color[0]-=15;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
