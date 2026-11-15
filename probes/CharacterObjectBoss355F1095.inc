// F1095: independent Japanese original game action 0x355,
// 00514FE8..005154ED = 1285 original CODE B /270 native x86.
// One authentic state inside the still-NONEXACT 81KB CharacterObject.
case 0x355: {
    if (owner->action>0x45 &&
        owner->action<0x96) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<10;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=10.0f;
        F1037_MOTION(this).yMotion=6.0f;
        field0D8=0;
        field0DA=0;
        field0DC=0;
        field080=0;
        field07C=0;
    }
    if (scaleX<g_F1095_ScaleCeilingAt00659898) {
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
    } else if (field0D8==0) {
        field080=10;
        ++field0D8;
    }
    if (F1037_MOTION(this).xMotion>g_F1059_ScaleRatioAt00657478) {
        F1037_MOTION(this).xMotion=F1037_MOTION(this).xMotion-g_F1059_ScaleRatioAt00657478;
        if (F1037_MOTION(this).xMotion<g_F1059_ScaleRatioAt00657478)
            F1037_MOTION(this).xMotion=0.5f;
    }
    if (field0DC==0) {
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1062_ScaleStepAt006583F8;
        if (F1037_MOTION(this).yMotion<g_F1095_LowerYAt00659894)
            field0DC=1;
    }
    if (field0DC==1) {
        F1037_MOTION(this).yMotion=(*(&F1037_MOTION(this).yMotion))+g_F1062_ScaleStepAt006583F8;
        if (F1037_MOTION(this).yMotion>g_F1095_UpperYAt00659890)
            field0DC=0;
    }
    if (field07C==4 && field080>0)
        field07C=0;
    if (field07C!=0 && F1024_PHASE(this).stageAt62<0x1F) {
        SetAuxActionAt0040FB40(0x1F);
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        field0DC=2;
    }
    if (F1024_PHASE(this).stageAt62==0x1F) {
        scaleX=(scaleX)+g_F1051_ScaleStepAt00658348;
        scaleY=(scaleY)+g_F1051_ScaleStepAt00658348;
        color[0]=unsigned char(color[0]-25);
    }
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==0x1F && F1024_PHASE(this).frameAt64==0) {
        if (field0DA<6) {
            ++field0DA;
            SetAuxActionAt0040FB40(1);
            return;
        }
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        field0DC=2;
    }
    return;
}
