    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<8) {
        PlaySoundAt453D40(R1190_CYCLE_SOUND);
        F32(0x314)=float(S16(0xF00));
        if (S16(0xF02)==0) {
            SpawnFloatXYAt453A70(R1190_EFFECT0,float(*reinterpret_cast<signed char*>(RAW+0x66)*18)+F32(0x44),
                (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
        }
        // Both actual native tests remain; do not simplify the second one.
        if (S16(0xF02)==1 && S16(0xF02)<0x43) {
            SpawnFloatXYAt453A70(R1190_EFFECT1,float(*reinterpret_cast<signed char*>(RAW+0x66)*18)+F32(0x44),
                (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
        }
        if (S16(0xF02)==2) {
            SpawnFloatXYAt453A70(R1190_EFFECT2,float(*reinterpret_cast<signed char*>(RAW+0x66)*18)+F32(0x44),
                (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
        }
        ++S16(0xF02);
        if (S16(0xF02)>2) S16(0xF02)=0;
    }
