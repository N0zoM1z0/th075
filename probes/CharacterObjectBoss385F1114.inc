// F1114: genuine original Japanese action 0x385 at 0051AFF0..0051B21D:
// 557 original CODE bytes/114 x86, in ONE NONEXACT 81KB game callable.
case 0x385: {
    if (reinterpret_cast<signed short&>(owner->field3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (field07C==6) {
        ++reinterpret_cast<signed short&>(field080);
        field07C=0;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        reinterpret_cast<signed short&>(field0D8)=0;
        scaleX=1.0f;
        scaleY=2.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=15.0f;
    }
    if (F1024_PHASE(this).stageAt62==2) {
        scaleX=float(RandomBoundaryAt00455580(0,6))*
            g_F1057_SpeedScaleAt006590B4+g_F1114_RandomOffsetAt00659094;
        scaleY=(*(&scaleX))+g_F1051_ScaleCeilingAt0065747C;
    }
    if (F1024_PHASE(this).stageAt62>2)
        scaleX=(scaleX)*g_F1114_FadeAt00659240;
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==3 && F1024_PHASE(this).frameAt64==0) {
        if (reinterpret_cast<signed short&>(field0D8)<9) {
            ++reinterpret_cast<signed short&>(field0D8);
            SetAuxActionAt0040FB40(2);
        } else {
            scaleX=1.8f;
            scaleY=1.0f;
        }
    }
    return;
}
