// F669: 0x255/0x256/0x257 authentic original fighter inner case C++.
// This is source-backed original stage movement/shots in the still NONEXACT
// full giant 00543210, not independently accepted whole game functions.
// The identity float lvalue expression preserves original FLD/FADD order.
case 0x255: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ResetAt453E20();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                SetAuxActionAt40FB40(6);
            }
            break;
        }
        case 0x256: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ResetAt453E20();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }

            break;
        }
        case 0x257: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ResetAt453E20();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                SetAuxActionAt40FB40(6);
            }
            break;
        }
