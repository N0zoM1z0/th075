// F1075: genuine original Japanese CharacterObject action 0x347 at
// 005123B9..005125A8, original 495 CODE B /101 ordered x86.
// This is an INNER state inside ONE nonexact original 81KB Boss.
case 0x347: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        scaleX=0.5f;
        scaleY=0.5f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field01A)=0x4E2;
        rotationX=-30.0f;
        rotationY=float(int(facing) * 25);
        reinterpret_cast<signed short&>(field0D8)=0;
    }
    scaleX =
        (g_F1075_CeilingAt00658058 -
            float(reinterpret_cast<signed short&>(field0D8))*g_F1075_StepAt006598A0 *
            int(reinterpret_cast<signed short&>(field0D8)<10)) +
        g_F1061_OffsetAt00658354 + scaleX;
    scaleY =
        (g_F1075_CeilingAt00658058 -
            float(reinterpret_cast<signed short&>(field0D8))*g_F1075_StepAt006598A0 *
            int(reinterpret_cast<signed short&>(field0D8)<10)) +
        g_F1061_OffsetAt00658354 + scaleY;
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>20)
            color[0]-=20;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
