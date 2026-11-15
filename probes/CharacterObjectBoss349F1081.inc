// F1081: original Japanese game 00512815..005129C1, 428 original
// CODE bytes /94 x86 within ONE still nonexact CharacterObject boss.
case 0x349: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
    }
    reinterpret_cast<unsigned int&>(x)=reinterpret_cast<unsigned int&>(owner->x);
    F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+g_F1081_ParentYOffsetAt00658268;
    rotationZ=(rotationZ)-g_F1081_AngleStepAt00657874;
    if (F1024_PHASE(this).stageAt62==1) {
        if (owner->action!=0x2BE ||
            (owner->action==0x2BE &&
             owner->animationStage>8))
            SetAuxActionAt0040FB40(2);
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>25)
            color[0]-=25;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    return;
}
