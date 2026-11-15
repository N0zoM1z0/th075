// F1052: native 0050B654..0050B821, action 0x325, 461 real CODE B /100 x86.
// This is a case of the ONE original 81KB CharacterObject, still nonexact.
case 0x325: {
    if (reinterpret_cast<signed short&>(owner->action)>49 &&
        reinterpret_cast<signed short&>(owner->action)<150 &&
        F1024_PHASE(this).stageAt62<2) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<3;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4, reinterpret_cast<unsigned int&>(x), reinterpret_cast<unsigned int&>(y),1,1);
        }
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3, reinterpret_cast<unsigned int&>(x), reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(0x17);
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
