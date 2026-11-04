// F1123: real Japanese original 0x38F 0051CAB0..0051CB4A,
// 154 native CODE B /32 x86 inside ONE NONEXACT 81KB parent.
case 0x38F: {
    if (PARENT_FIELD(signed short,0x3A0)<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
