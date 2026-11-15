// F1131: genuine Japanese native 0x3E3 at PE 0051D70F..0051DAE8,
// original 985 CODE B/200 x86 inside ONE nonexact 81KB game callable.
case 0x3E3: {
    facing=1;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=-1.0f;
        field0D8=short(RandomBoundaryAt00455580(0,360)-180);
        field0DA=15;
    }
    if (F1024_PHASE(this).stageAt62==0) {
        --field0DA;
        if (field0DA<3)
            field0DA=3;
        SetNativeTwoFloatsAt0040FB70(float(field0D8),
            float(field0DA)*g_F1120_XBrakingAt00659090);
    }
    if (F1024_PHASE(this).stageAt62==1) {
        field0D8=short(F1057_FloatAtan2At00483300(
            (*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888-F1037_POSITION(this).yPosition,
            F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition) /
            g_F1057_AngleDivAt00657828);
        SetNativeTwoFloatsAt0040FB70(float(field0D8),20.0f);
        if (F1037_POSITION(this).xPosition-F1037_POSITION(PARENT_GRANDPARENT).xPosition<g_F1115_DistanceAt0065786C &&
            F1037_POSITION(this).xPosition-F1037_POSITION(PARENT_GRANDPARENT).xPosition>g_F1131_LeftHitAt00659230 &&
            F1037_POSITION(this).yPosition-F1037_POSITION(PARENT_GRANDPARENT).yPosition<g_F1131_TopHitAt006590A8 &&
            F1037_POSITION(this).yPosition-F1037_POSITION(PARENT_GRANDPARENT).yPosition>g_F1131_BottomHitAt00658268) {
            NativeParentExpiredAt0045B830();
            if (owner->opponent->field366<2)
                ++owner->opponent->field366;
            else {
                owner->opponent->field2D0+=0x4E20;
            }
            NativeHitAt0045B860(0x2E);
            return;
        }
    }
    F1037_POSITION(this).xPosition=F1037_POSITION(this).xPosition+F1037_MOTION(this).xMotion;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==field070)
        SetAuxActionAt0040FB40(1);
    return;
}
