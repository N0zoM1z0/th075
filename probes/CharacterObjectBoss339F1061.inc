// F1061: authentic original CharacterObject action 0x339 at
// 0050ED70..0050EF5F, original 495 CODE B /101 ordered x86.
// This is an INNER state inside ONE nonexact original 81KB Boss.
case 0x339: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(float,0x1C)=0.5f;
        SELF_FIELD(float,0x20)=0.5f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(signed short,0x1A)=0x4E2;
        SELF_FIELD(float,0x28)=-30.0f;
        SELF_FIELD(float,0x2C)=float(int(SELF_FIELD(signed char,0x66)) * -45);
        SELF_FIELD(signed short,0xD8)=0;
    }
    SELF_FIELD(float,0x1C) =
        (g_F1061_CeilingAt006583FC -
            float(SELF_FIELD(signed short,0xD8))*g_F1061_StepAt0065972C *
            int(SELF_FIELD(signed short,0xD8)<10)) +
        g_F1061_OffsetAt00658354 + SELF_FIELD(float,0x1C);
    SELF_FIELD(float,0x20) =
        (g_F1061_CeilingAt006583FC -
            float(SELF_FIELD(signed short,0xD8))*g_F1061_StepAt0065972C *
            int(SELF_FIELD(signed short,0xD8)<10)) +
        g_F1061_OffsetAt00658354 + SELF_FIELD(float,0x20);
    if (F1024_PHASE(this).stageAt62>1) {
        if (SELF_FIELD(unsigned char,0x11)>20)
            SELF_FIELD(unsigned char,0x11)-=20;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    return;
}
