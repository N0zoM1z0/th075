// F1054: Real native action 0x337, original 155B/35 x86; one 81KB parent.
case 0x337: {
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if (GetNativeActionAt0040FA30() == reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
