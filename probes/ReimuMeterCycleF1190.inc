    if ((animationStage)==10 && (animationFrame)==0 && (scriptCounterF00)<8) {
        PlaySound(R1190_CYCLE_SOUND);
        field314=float(scriptCounterF00);
        if ((scriptCounterF02)==0) {
            SpawnBattleEffect(R1190_EFFECT0,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        }
        // Both actual native tests remain; do not simplify the second one.
        if ((scriptCounterF02)==1 && (scriptCounterF02)<0x43) {
            SpawnBattleEffect(R1190_EFFECT1,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        }
        if ((scriptCounterF02)==2) {
            SpawnBattleEffect(R1190_EFFECT2,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        }
        ++scriptCounterF02;
        if ((scriptCounterF02)>2) scriptCounterF02=0;
    }
