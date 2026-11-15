// F1129 original native TH075 0x3E6 at 0051E215..0051E3F4:
// genuine 479 original CODE B /105 x86, one switch interior of
// the same still-NONEXACT original 81KB CharacterObject::Advance.
case 0x3E6: {
    if (owner->action!=0xD1 &&
        owner->action!=0xD2 &&
        F1024_PHASE(this).stageAt62<2) {
        SetAuxActionAt0040FB40(2);
        return;
    }
    reinterpret_cast<unsigned int&>(x)=reinterpret_cast<unsigned int&>(owner->x);
    F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+g_F1057_YOffsetAt00657888;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationX=0.0f;
        rotationY=0.0f;
        rotationZ=0.0f;
    }
    scaleX=(scaleX)-g_F1057_SpeedBaseAt006590BC;
    scaleY=(scaleY)-g_F1057_SpeedBaseAt006590BC;
    rotationZ=(rotationZ)+g_F1051_ScaleCeilingAt0065747C;
    if (F1024_PHASE(this).stageAt62==2)
        color[0]=unsigned char(color[0]-12);
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
