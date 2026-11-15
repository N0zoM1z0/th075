    if ((animationStage)==10 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        PlaySoundAt453D40(R1190_CYCLE_SOUND);
        field314=float(reinterpret_cast<signed short&>(scriptCounterF00));
        if ((reinterpret_cast<signed short&>(scriptCounterF02))==0) {
            SpawnFloatXYAt453A70(R1190_EFFECT0,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        }
        // Both actual native tests remain; do not simplify the second one.
        if ((reinterpret_cast<signed short&>(scriptCounterF02))==1 && (reinterpret_cast<signed short&>(scriptCounterF02))<0x43) {
            SpawnFloatXYAt453A70(R1190_EFFECT1,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF02))==2) {
            SpawnFloatXYAt453A70(R1190_EFFECT2,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        }
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>2) reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
