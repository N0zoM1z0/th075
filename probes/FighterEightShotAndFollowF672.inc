// F672: original fighter 00543210 full native 259..25D C++ case grammar.
// These five complete original source bodies remain NONSTRICT from real
// EBP integer-to-float scratch slot differences. Do NOT count exact.
// 259 contains eight original 321/322 shots; 25A..25D each one shot.
// Original PE global 00658264 is shared by 259 and 25B.
        case 0x259: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ResetAt453E20();
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                StartAnimationAt46D000(250);
                field314=-10.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(facing*40)+(x),
                    (*(&y))+g_EightShotY0At006591F8,
                    facing,1);
                SpawnFloatXYAt453A70(0x322,
                    float(facing*40)+(x),
                    (*(&y))+g_EightShotY0At006591F8,
                    facing,1);
                field314=10.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(facing*40)+(x),
                    (*(&y))+g_EightShotY1At00658264,
                    facing,1);
                SpawnFloatXYAt453A70(0x322,
                    float(facing*40)+(x),
                    (*(&y))+g_EightShotY1At00658264,
                    facing,1);
                field314=-6.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(facing*75)+(x),
                    (*(&y))+g_BarrageY3At0065908C,
                    facing,1);
                SpawnFloatXYAt453A70(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_BarrageY3At0065908C,
                    facing,1);
                field314=6.0f;
                SpawnFloatXYAt453A70(0x321,
                    float(facing*75)+(x),
                    (*(&y))+g_EightShotY2At00658268,
                    facing,1);
                SpawnFloatXYAt453A70(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_EightShotY2At00658268,
                    facing,1);
            }
            break;
        }
        case 0x25A: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=(velocityX)*g_BounceScaleAt00657F74;
                velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
                field07C=1;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnFloatXYAt453A70(0x32B,
                    float(facing*100)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x25B: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=(velocityX)*g_BounceScaleAt00657F74;
                velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
                field07C=1;
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnFloatXYAt453A70(0x32D,
                    float(facing*100)+(x),
                    (*(&y))+g_EightShotY1At00658264,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x25C: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ResetAt453E20();
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnFloatXYAt453A70(0x332,
                    float(facing*70)+(x),
                    (*(&y))+g_OneShotYAt0065928C,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
            break;
        }
        case 0x25D: {
            if ((animationStage)==0 && (animationFrame)==0) {
                field07C=1;
                ResetAt453E20();
            }
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnFloatXYAt453A70(0x333,
                    float(facing*70)+(x),
                    (*(&y))+g_OneShotYAt0065928C,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
            break;
        }
