        F32(0x318)=R1187_SPEED;
        F32(0x314)=float(R1187_ANGLE_BIAS-SelectRangeAt455580(0,R1187_UPPER));
        SpawnFloatXYAt453A70(R1187_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1187_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1187_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(R1187_ANIMATION);
