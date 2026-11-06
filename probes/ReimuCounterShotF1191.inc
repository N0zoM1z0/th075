        F32(0x318)=0.0f;
        F32(0x314)=float(R1191_ANGLE_EXPR);
        SpawnFloatXYAt453A70(0x391,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1191_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1191_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
        PlaySoundAt453D40(0);
        ++S16(0xF00);
