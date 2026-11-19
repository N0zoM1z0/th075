// F718: complete physical 00543210 action 2DD /2DE original native source.
// 2DD 0054EAAB..0054ED53: 680 B /189 native x86.
// 2DE 0054ED53..0054EFE7: 660 B /189 native x86.
// Native behavioral branches and typed PE calls retained; whole giant NONEXACT.
        case 0x2DD: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
                PlaySound(11);
                velocityY=10.0f;
                velocityX=30.0f;
                field05C=0.45f;
                reinterpret_cast<signed short&>(scriptCounterF00)=1;
            }
            if ((animationStage)<9 && y>g_ThresholdAt0065782C && (animationStage)>3) {
                velocityX=(velocityX)-g_NewDragAt006581E0;
                velocityY=velocityY-field05C;
                if ((velocityX)<g_StopThresholdAt00657480)
                    velocityX=2.0f;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(9);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if ((animationStage)<4) {
                SpawnFloatXYAt453A70(0x329,
                    float(facing*62)+(x),
                    (*(&y))+g_F714_ShotYAt00657868,
                    facing,1);
                SpawnFloatXYAt453A70(0x387,
                    float(facing*62)+(x),
                    (*(&y))+g_F714_ShotYAt00657868,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0);
                aiCardTimer=static_cast<short>(RandomBoundaryAt455580(100,180)
                      -static_cast<int>(g_CloudOpponentAt006714D0)*30);
            }
            if ((animationFrame)==0)
                field07C=0;
            if ((animationStage)==4 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<4) {
                SetAuxActionAt40FB40(0);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                break;
            }
            if ((animationStage)==9 && (animationFrame)==0)
                SetAuxActionAt40FB40(7);
            break;
        }
        case 0x2DE: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=99;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)<25 && y>g_ThresholdAt0065782C && (animationStage)>14) {
                velocityX=(velocityX)-g_F718_FallingDragAt00659090;
                velocityY=velocityY-field05C;
                if ((velocityX)<g_F718_BounceMinAt00657CF8)
                    velocityX=3.0f;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(25);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0);
                aiCardTimer=static_cast<short>(RandomBoundaryAt455580(100,180)
                      -static_cast<int>(g_CloudOpponentAt006714D0)*30);
            }
            if ((animationFrame)==0)
                field07C=0;
            if ((animationStage)==7 && (animationFrame)==0) {
                SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
                PlaySound(11);
                velocityY=9.0f;
                velocityX=20.0f;
                field05C=0.8f;
            }
            if ((animationStage)>6 && (animationStage)<16) {
                SpawnFloatXYAt453A70(0x329,
                    float(facing*62)+(x),
                    (*(&y))+g_F714_ShotYAt00657868,
                    facing,1);
            }
            if ((animationStage)==16 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<3) {
                SetAuxActionAt40FB40(12);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                break;
            }
            if ((animationStage)==25 && (animationFrame)==0)
                SetAuxActionAt40FB40(23);
            break;
        }
