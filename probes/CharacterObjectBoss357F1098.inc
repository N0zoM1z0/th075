// F1098: genuine Japanese original 005159A0..00515C0E,
// 622 original CODE B /131 x86, one interior of NONEXACT 81KB boss.
case 0x357: {
    if (reinterpret_cast<signed short&>(owner->action)>0x31 &&
        reinterpret_cast<signed short&>(owner->action)<0x96 &&
        F1024_PHASE(this).stageAt62<0x17) {
        SetAuxActionAt0040FB40(0x17);
        return;
    }
    if (reinterpret_cast<signed short&>(owner->action)==0x189 && F1024_PHASE(this).stageAt62<0x17) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(facing*120);
        F1037_POSITION(this).yPosition=120.0f;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<signed short&>(field0DA)=0;
    }
    if (reinterpret_cast<signed short&>(field0D8)==0) {
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
            color[0]=unsigned char(color[0]+25);
        } else {
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
        }
        if (color[0]==0xFF && reinterpret_cast<signed short&>(field0D8)==0) {
            ++reinterpret_cast<signed short&>(field0D8);
            reinterpret_cast<signed short&>(field080)=1;
        }
    }
    if (reinterpret_cast<signed short&>(owner->field082)==0 &&
        GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    return;
}
