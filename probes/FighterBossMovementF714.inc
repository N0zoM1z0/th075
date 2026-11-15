// F714: original physical native 00543210 action 2DC, complete 602B/169-x86.
// Real bounded handler: startup, floor motion, two native 0x333/0x387
// float projectiles, difficulty gate, terminal counter and state 4.
// Source-backed nonexact giant; never accept this as a whole game function.
        case 0x2DC: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=1;
                PrepareActionAt453D40(11);
                velocityY=-10.0f;
                velocityX=30.0f;
                field05C=0.8f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))<4 && y>g_ThresholdAt0065782C) {
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(4);
                    y=0.0f;
                    velocityY=0.0f;
                    field05C=0.0f;
                    break;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))<4) {
                SpawnFloatXYAt453A70(0x333,
                    float(facing*62)+(x),
                    (*(&y))+g_F714_ShotYAt00657868,
                    facing,1);
                if (g_CloudOpponentAt006714D0>1)
                    SpawnFloatXYAt453A70(0x387,
                        float(facing*62)+(x),
                        (*(&y))+g_F714_ShotYAt00657868,
                        facing,1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))>3 && (velocityX)>g_ThresholdAt0065782C) {
                velocityX=(velocityX)-g_F714_DecelerationAt0065747C;
                if ((velocityX)<g_ThresholdAt0065782C)
                    velocityX=0.0f;
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(RandomBoundaryAt455580(100,180)
                    -static_cast<int>(g_CloudOpponentAt006714D0)*30);
            }
            if ((reinterpret_cast<signed short&>(animationFrame))==0)
                field07C=0;
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
                SetAuxActionAt40FB40(0);
            break;
        }
