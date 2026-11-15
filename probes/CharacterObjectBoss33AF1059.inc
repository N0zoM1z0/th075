// F1059 genuine Japanese native 0050EF5F..0050F25A (763 CODE B /168 x86).
// This is one INNER action in the ONE still-NONEXACT 81KB CharacterObject.
case 0x33A: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        reinterpret_cast<signed short&>(field0D8)=short(RandomBoundaryAt00455580(0,13)+12);
        reinterpret_cast<signed short&>(field0DA)=short(RandomBoundaryAt00455580(0,0x167));
        scaleX=float(RandomBoundaryAt00455580(0,30)+20)*g_F1059_ScaleBaseAt006590B4;
        scaleY=(scaleX)*g_F1059_ScaleRatioAt00657478;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    --reinterpret_cast<signed short&>(field0D8);
    if (reinterpret_cast<signed short&>(field0D8)<4)
        reinterpret_cast<signed short&>(field0D8)=4;
    SetNativeTwoFloatsAt0040FB70(float(reinterpret_cast<signed short&>(field0DA)),float(reinterpret_cast<signed short&>(field0D8)));
    rotationZ=F1057_FloatAtan2At00483300(
        F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion + F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    scaleX=(scaleX)*g_F1059_ScaleFadeAt006598A8;
    scaleY=(scaleY)*g_F1059_ScaleFadeAt006598A8;
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1059_UpperBoundAt00657884 ||
        F1037_POSITION(this).yPosition<g_F1059_LowerBoundAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>=10)
            color[0]-=10;
        else
            color[0]=0;
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
