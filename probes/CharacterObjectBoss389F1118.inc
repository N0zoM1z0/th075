// F1118: genuine Japanese 0x389 action, original PE
// 0051BB8B..0051BFE2: 1111 CODE B/238 x86, within ONE
// still-NONEXACT 81KB CharacterObject::Advance.
case 0x389: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (field07C==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field0D8)=short(RandomBoundaryAt00455580(0,300)+200);
        reinterpret_cast<signed short&>(field0DA)=short(RandomBoundaryAt00455580(0,50)+45);
        reinterpret_cast<signed short&>(field0DC)=short(RandomBoundaryAt00455580(0,15)+5);
        SetNativeTwoFloatsAt0040FB70(
            float(reinterpret_cast<signed short&>(field0DA)),
            float(reinterpret_cast<signed short&>(field0D8))*g_F1057_SpeedScaleAt006590B4);
    }
    if (F1024_PHASE(this).stageAt62<=1) {
        SetNativeTwoFloatsAt0040FB70(
            float(reinterpret_cast<signed short&>(field0DA)),
            float(reinterpret_cast<signed short&>(field0D8))*g_F1057_SpeedScaleAt006590B4);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x33C,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
        scaleX=float(double(RandomBoundaryAt00455580(0,4)-2)*
            g_F1057_RandomDoubleAt00658A20+g_F1057_RandomBaseAt00657D00);
        reinterpret_cast<unsigned int&>(scaleY)=reinterpret_cast<unsigned int&>(scaleX);
        // Native ordinal-101 JG skips the entire signed-speed decay:
        // only action stages <=1 decrement/clamp speed +0xD8.
        reinterpret_cast<signed short&>(field0D8)=short(reinterpret_cast<signed short&>(field0D8)-15);
        if (reinterpret_cast<signed short&>(field0D8)<reinterpret_cast<signed short&>(field0DC))
            reinterpret_cast<signed short&>(field0D8)=reinterpret_cast<signed short&>(field0DC);
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (field07C!=0 && field07C!=6 && F1024_PHASE(this).stageAt62==1) {
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        SetAuxActionAt0040FB40(2);
        scaleX=2.5f;
        scaleY=2.5f;
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        scaleX=(scaleX)*g_F1055_FadeScaleAt006598A4;
        scaleY=(scaleY)*g_F1055_FadeScaleAt006598A4;
        if (color[0]>=25)
            color[0]-=25;
        else {
            color[0]=0;
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
