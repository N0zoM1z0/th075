// F1089: original Japanese 0x350, native 00514048..00514537,
// 1263 CODE B /273 x86 inside ONE nonexact original 81KB boss.
case 0x350: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        if (reinterpret_cast<signed short&>(field0D8)!=140)
            reinterpret_cast<signed short&>(field0D8)=0;
    }
    SetNativeTwoFloatsAt0040FB70(
        float(reinterpret_cast<signed short&>(owner->fieldF0C))+
            g_F1085_ParentMultiplierAt0065989C*static_cast<const float&>(field0C8),
        float(reinterpret_cast<signed short&>(field0D8)));
    F1037_POSITION(this).xPosition=F1037_MOTION(this).xMotion+F1037_POSITION(PARENT).xPosition;
    F1037_POSITION(this).yPosition=(*(&F1037_MOTION(this).yMotion))*g_F1085_ParentYMultiplierAt00657F74+
        F1037_POSITION(PARENT).yPosition+g_F1085_YOffsetAt0065835C;
    if (reinterpret_cast<signed short&>(field0D8)<140)
        reinterpret_cast<signed short&>(field0D8)=short(reinterpret_cast<signed short&>(field0D8)+5);
    else
        reinterpret_cast<signed short&>(field0D8)=140;
    if ((reinterpret_cast<signed short&>(owner->opponent->health)<=0 ||
        reinterpret_cast<signed short&>(owner->health)<=0 ||
        reinterpret_cast<signed short&>(owner->field3A0)<=0) &&
        F1024_PHASE(this).stageAt62<2)
        SetAuxActionAt0040FB40(2);
    if (reinterpret_cast<signed short&>(owner->action)==0x2C1 &&
        reinterpret_cast<signed short&>(owner->animationStage)==2 &&
        F1024_PHASE(this).stageAt62<2)
        SetAuxActionAt0040FB40(2);
    if (F1024_PHASE(this).stageAt62==0) {
        if ((reinterpret_cast<signed short&>(owner->action)==0x192 && reinterpret_cast<signed short&>(owner->animationStage)==4) ||
            (reinterpret_cast<signed short&>(owner->action)==0x260 && reinterpret_cast<signed short&>(owner->animationStage)==4) ||
            (reinterpret_cast<signed short&>(owner->action)==0x261 && reinterpret_cast<signed short&>(owner->animationStage)==4) ||
            (reinterpret_cast<signed short&>(owner->action)==0x262 && reinterpret_cast<signed short&>(owner->animationStage)==4)) {
            for (int shot=0;shot<8;++shot) {
                owner->field314=float(shot*45);
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x364,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
                    owner->facing,1);
            }
            SetAuxActionAt0040FB40(2);
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(4);
        }
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>10)
            color[0]-=10;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (F1024_PHASE(this).stageAt62==1 &&
        reinterpret_cast<signed short&>(owner->action)==0x2C1 &&
        reinterpret_cast<signed short&>(owner->animationStage)==3) {
        SetAuxActionAt0040FB40(0);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(20);
        return;
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0) {
        SetAuxActionAt0040FB40(0);
        owner->field36C=(owner->field36C)-g_F1085_LastYAt006592A4;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(20);
    }
    return;
}
