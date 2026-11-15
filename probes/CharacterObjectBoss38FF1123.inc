// F1123: real Japanese original 0x38F 0051CAB0..0051CB4A,
// 154 native CODE B /32 x86 inside ONE NONEXACT 81KB parent.
case 0x38F: {
    if (owner->field3A0<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        field0D8=0;
        field080=1;
        field07C=0;
    }
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    return;
}
