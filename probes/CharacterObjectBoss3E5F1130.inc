// F1130: original Japanese 0x3E5 at 0051E01F..0051E215:
// 502 native original CODE B /96 x86 inside ONE nonexact 81KB Boss.
case 0x3E5: {
    reinterpret_cast<unsigned int&>(x)=reinterpret_cast<unsigned int&>(owner->x);
    F1037_POSITION(this).yPosition=0.0f;
    reinterpret_cast<signed short&>(field08A)=1;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=3.0f;
        scaleY=3.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field01A)=0x4E2;
        rotationY=0.0f;
        rotationZ=0.0f;
        rotationX=-80.0f;
        reinterpret_cast<signed short&>(field0D8)=reinterpret_cast<signed short&>(owner->field3A0);
    }
    if (reinterpret_cast<signed short&>(owner->field3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    scaleX=float(reinterpret_cast<signed short&>(owner->field3A0))/reinterpret_cast<signed short&>(field0D8)*2.0f;
    scaleY=float(reinterpret_cast<signed short&>(owner->field3A0))/reinterpret_cast<signed short&>(field0D8)*2.0f;
    rotationZ=(rotationZ)+g_F1051_ScaleCeilingAt0065747C;
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070)) {
        SetAuxActionAt0040FB40(10);
        return;
    }
    return;
}
