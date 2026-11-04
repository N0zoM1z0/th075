// F1105: original Japanese game action 0x35F at 00516CE4..00516D10,
// genuine 44 native CODE B /10 x86, interior of ONE nonexact 81KB boss.
case 0x35F: {
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
