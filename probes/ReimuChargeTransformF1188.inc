// Actual transform/color progression shared by the five Reimu charge states.
    if (S16(0x62)==R1188_FADE_STAGE && S16(0x64)==0) {
        SetMotionFloatAt40FBB0(0.0f,100.0f,0.0f);
        F32(0x1C)=1.0f; F32(0x20)=1.0f;
        U8(0x11)=255; U8(0x12)=255; U8(0x13)=255; U8(0x14)=255;
        PlaySoundAt453D40(2);
    }
    if (S16(0x62)==R1188_FADE_STAGE) {
        F32(0x1C)=F32(0x1C)-g_ProjectileFallAt006590B4;
        F32(0x20)=(*(&F32(0x20)))+g_ReimuAirDragAt00658348;
        U8(0x11)=U8(0x11)-25;
    }
    if (S16(0x62)==R1188_RETURN_STAGE) {
        if (F32(0x1C)<g_AnimationDeltaAt0065747C) {
            F32(0x1C)=(*(&F32(0x1C)))+g_ProjectileFallAt006590B4;
            F32(0x20)=F32(0x20)-g_ReimuAirDragAt00658348;
            U8(0x11)=U8(0x11)+25;
        } else {
            F32(0x1C)=1.0f; F32(0x20)=1.0f; U8(0x11)=255;
        }
    }
