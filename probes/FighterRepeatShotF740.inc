// F740: two complete original repeated 0x330 volleys, part of the ONE
// 00543210 giant. Original 196 0054991A..00549ACE, 197
// 00549ACE..00549C82: each 436 native CODE bytes/118 x86.
// Real game-stage reset, motion, physical globals, and 6-shot gate.
// Original complete fighter CODE remains NONEXACT; no fake locals.
        case 0x196: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (GetNativeActionAt40FA30()==(field070))
                SetNativeActionAt40FAC0(0);
            if ((animationStage)==6 && (animationFrame)==0) {
                PrepareActionAt453D40(2);
                field314=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*60)+(x),
                    (*(&y))+g_F740_ShotY0At00659A1C,
                    facing,1);
                UpdateGaugeTimer(100);
            }
            if ((animationStage)==7 && (animationFrame)==0 && static_cast<unsigned int>(inputA)>0
                    && (reinterpret_cast<signed short&>(scriptCounterF00))<6 && (spirit)>0) {
                PrepareActionAt453D40(2);
                field314=0.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*60)+(x),
                    (*(&y))+g_F740_ShotY0At00659A1C,
                    facing,1);
                UpdateGaugeTimer(10);
                SetAuxActionAt40FB40(6);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
        case 0x197: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (GetNativeActionAt40FA30()==(field070))
                SetNativeActionAt40FAC0(0);
            if ((animationStage)==6 && (animationFrame)==0) {
                PrepareActionAt453D40(2);
                field314=30.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*68)+(x),
                    (*(&y))+g_F740_ShotY1At0065928C,
                    facing,1);
                UpdateGaugeTimer(100);
            }
            if ((animationStage)==7 && (animationFrame)==0 && static_cast<unsigned int>(inputA)>0
                    && (reinterpret_cast<signed short&>(scriptCounterF00))<6 && (spirit)>0) {
                PrepareActionAt453D40(2);
                field314=20.0f;
                SpawnFloatXYAt453A70(0x330,
                    float(facing*68)+(x),
                    (*(&y))+g_F740_ShotY1At0065928C,
                    facing,1);
                UpdateGaugeTimer(10);
                SetAuxActionAt40FB40(6);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
        case 0x198: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ClearMotionFields();
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                PrepareActionAt453D40(1);
                field314=60.0f;
                UpdateGaugeTimer(250);
                SpawnFloatXYAt453A70(0x347,
                    float(facing*28)+(x),
                    (*(&y))+g_F740_ShotY2At00659A18,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070))
                SetNativeActionAt40FAC0(2);
            break;
        }
