// Actual transform/color progression shared by the five Reimu charge states.
    if ((animationStage)==R1188_FADE_STAGE && (animationFrame)==0) {
        SetMotionFloatAt40FBB0(0.0f,100.0f,0.0f);
        scaleX=1.0f; scaleY=1.0f;
        color[0]=255; color[1]=255; color[2]=255; color[3]=255;
        PlaySoundAt453D40(2);
    }
    if ((animationStage)==R1188_FADE_STAGE) {
        scaleX=(scaleX)-g_ProjectileFallAt006590B4;
        scaleY=(*(&scaleY))+g_ReimuAirDragAt00658348;
        color[0]=(color[0])-25;
    }
    if ((animationStage)==R1188_RETURN_STAGE) {
        if ((scaleX)<g_AnimationDeltaAt0065747C) {
            scaleX=(*(&scaleX))+g_ProjectileFallAt006590B4;
            scaleY=(scaleY)-g_ReimuAirDragAt00658348;
            color[0]=(color[0])+25;
        } else {
            scaleX=1.0f; scaleY=1.0f; color[0]=255;
        }
    }
