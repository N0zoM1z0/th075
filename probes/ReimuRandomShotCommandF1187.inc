        field318=R1187_SPEED;
        field314=float(R1187_ANGLE_BIAS-SelectRangeAt455580(0,R1187_UPPER));
        SpawnFloatXYAt453A70(R1187_EFFECT,float(facing*R1187_X_OFFSET)+(x),
            (*(&y))+R1187_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(R1187_ANIMATION);
