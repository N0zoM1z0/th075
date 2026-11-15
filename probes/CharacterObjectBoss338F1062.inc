// F1062: actual Japanese PE 0050EA5B..0050ED70 action 0x338,
// 789 native CODE B /175 x86 in ONE nonexact 81KB CharacterObject.
case 0x338: {
    if (reinterpret_cast<signed short&>(owner->action)>0x45 &&
        reinterpret_cast<signed short&>(owner->action)<0x96) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<13;++shot) {
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
    if (reinterpret_cast<signed short&>(owner->action)==0x25C && reinterpret_cast<signed short&>(owner->animationStage)==0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<signed short&>(field080)=5;
        field07C=0;
    }
    if (F1024_PHASE(this).stageAt62==1) {
        scaleX=(scaleX)+g_F1062_ScaleStepAt006583F8;
        scaleY=(scaleY)+g_F1062_ScaleStepAt006583F8;
    }
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x337,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        if (reinterpret_cast<signed short&>(field0D8)<5 && reinterpret_cast<signed short&>(field080)>0) {
            field07C=0;
            ++reinterpret_cast<signed short&>(field0D8);
            SetAuxActionAt0040FB40(2);
            return;
        }
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(8);
    return;
}
