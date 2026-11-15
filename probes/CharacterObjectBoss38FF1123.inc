// F1123: real Japanese original 0x38F 0051CAB0..0051CB4A,
// 154 native CODE B /32 x86 inside ONE NONEXACT 81KB parent.
case 0x38F: {
    if (reinterpret_cast<signed short&>(owner->field3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
