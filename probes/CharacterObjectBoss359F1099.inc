// F1099 authentic Japanese original action 0x359 at 00515E7F..00515EF2,
// 115 native CODE B /24 x86, inside ONE nonexact original 81KB boss.
case 0x359: {
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
