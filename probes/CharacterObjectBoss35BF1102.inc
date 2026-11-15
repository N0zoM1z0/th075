// F1102 original Japanese 0x35B, native 00515F65..005163BA:
// 1109 native CODE B /233 x86 in ONE still-NONEXACT 81KB parent.
case 0x35B: {
    if (reinterpret_cast<signed short&>(owner->action)>0x31 &&
        reinterpret_cast<signed short&>(owner->action)<0x96 &&
        F1024_PHASE(this).stageAt62<0x17) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<8;++shot)
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=22.0f;
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<signed short&>(field0DA)=0;
        reinterpret_cast<signed short&>(field080)=0;
        field07C=0;
    }
    F1037_MOTION(this).xMotion=F1037_MOTION(this).xMotion-g_F1093_XStepAt00658048;
    if (F1037_MOTION(this).xMotion<g_F1051_ScaleCeilingAt0065747C)
        F1037_MOTION(this).xMotion=1.0f;
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
            reinterpret_cast<signed short&>(field080)=5;
        }
    }
    if (field07C==6) {
        field07C=0;
        ++reinterpret_cast<signed short&>(field080);
    }
    if (field07C==4 && reinterpret_cast<signed short&>(field080)>0)
        field07C=0;
    if (field07C!=0)
        reinterpret_cast<signed short&>(field080)=0;
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (reinterpret_cast<signed short&>(field080)==0 && F1024_PHASE(this).stageAt62<0x17 &&
        reinterpret_cast<signed short&>(field0D8)>0) {
        SetAuxActionAt0040FB40(0x17);
        return;
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0x17 && F1024_PHASE(this).frameAt64==0 &&
        reinterpret_cast<signed short&>(field0DA)<1) {
        SetAuxActionAt0040FB40(1);
        ++reinterpret_cast<signed short&>(field0DA);
    }
    return;
}
