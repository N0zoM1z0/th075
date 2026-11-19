        field318=R1187_SPEED;
        field314=float(R1187_ANGLE_BIAS-RecordedRange(0,R1187_UPPER));
        SpawnBattleEffect(R1187_EFFECT,float(facing*R1187_X_OFFSET)+(x),
            (*(&y))+R1187_Y_OFFSET,reinterpret_cast<char&>(facing),1);
        PlaySound(0);
        UpdateGaugeTimer(R1187_ANIMATION);
