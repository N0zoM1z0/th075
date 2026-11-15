        field318=0.0f;
        field314=float(R1191_ANGLE_EXPR);
        SpawnFloatXYAt453A70(0x391,float(facing*R1191_X_OFFSET)+(x),
            (*(&y))+R1191_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        PlaySoundAt453D40(0);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
