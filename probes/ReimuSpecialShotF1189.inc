        F32(0x314)=R1189_ANGLE;
        F32(0x318)=R1189_SPEED;
        SpawnFloatXYAt453A70(R1189_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*R1189_X_OFFSET)+F32(0x44),
            (*(&POS48))+R1189_Y_OFFSET,*reinterpret_cast<char*>(RAW+0x66),1);
