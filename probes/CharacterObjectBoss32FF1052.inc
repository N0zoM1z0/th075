// F1052: native 0050D097..0050D17A, action 0x32F, 227 original B/50 x86.
case 0x32F: {
    if (owner->action==0x133) {
        reinterpret_cast<unsigned int&>(x)=reinterpret_cast<unsigned int&>(owner->x);
        reinterpret_cast<unsigned int&>(y)=reinterpret_cast<unsigned int&>(owner->y);
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    return;
}
