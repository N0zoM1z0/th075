// F1082: original Japanese 005129C1..00512BA7, 486 native CODE B/102 x86.
// Real game action 0x34A inside ONE nonexact 81KB CharacterObject Advance.
case 0x34A: {
    reinterpret_cast<unsigned int&>(x)=reinterpret_cast<unsigned int&>(owner->x);
    y=0.0f;
    reinterpret_cast<signed short&>(field08A)=1;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=2.5f;
        scaleY=2.5f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field01A)=0x4E2;
        rotationY=0.0f;
        rotationZ=0.0f;
        rotationX=-80.0f;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(0x10);
    }
    if (F1024_PHASE(this).stageAt62==1) {
        // The original compares parent action +0x60 with 0x2C0, then
        // checks the parent's distinct +0x62 WORD against 0x2C0 and 6.
        // Do not collapse this to a simpler presumed stage condition.
        if (reinterpret_cast<signed short&>(owner->action)!=0x2C0 ||
            (reinterpret_cast<signed short&>(owner->animationStage)==0x2C0 &&
             reinterpret_cast<signed short&>(owner->animationStage)>6)) {
            SetAuxActionAt0040FB40(2);
            return;
        }
    }
    if (F1024_PHASE(this).stageAt62==2) {
        if (color[0]>15)
            color[0]-=15;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    rotationZ=(rotationZ)+g_F1051_ScaleCeilingAt0065747C;
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        NativeParentExpiredAt0045B830();
        return;
    }
    return;
}
