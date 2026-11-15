// F657: original fighter 00543210 physical stage 0x186..0x189 source grammar.
// Action 0x186 is deliberately still NONSTRICT (two original EBP−0x84
// temporary slots compile at EBP−0x20). Do not claim whole 186 exact.
// Three following full original native 187/188/189 cases are strictly
// compared against genuine original PE/typed COFF in the full parent.
        case 0x186: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if ((field3AC)==0) ResetAt453E20();
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                velocityX=10.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>0) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                InitTrajectoryAt453E60(2.0f);
                SpawnFloatXYAt453A70(0x325,
                    float(facing*170)+(x),
                    (y)-g_ApproachLowerAt00658290,
                    facing,0);
            }
            break;
        }
        case 0x187: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if ((field3AC)==0) ResetAt453E20();
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                velocityX=10.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>0) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            break;
        }
        case 0x188: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if ((field3AC)==0) ResetAt453E20();
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                velocityX=15.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>0) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(2);
            break;
        }
        case 0x189: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                field3AC=0;
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                field05C=0.0f;
                velocityY=0.0f;
                velocityX=15.0f;
            }
            if ((velocityX)>g_ThresholdAt0065782C) velocityX=(velocityX)-g_SlowPositiveDragAt006578C0;
            if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>6 && (reinterpret_cast<signed short&>(animationStage))<9) {
                velocityY=velocityY-field05C;
                if (velocityY+y<=g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    velocityY=0.0f;
                    field05C=0.0f;
                    y=0.0f;
                    reinterpret_cast<signed short&>(animationFrame)=0;
                    SetAuxActionAt40FB40(9);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=9.0f;
                field05C=0.9f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==9 && y>g_ThresholdAt0065782C)
                SetAuxActionAt40FB40((reinterpret_cast<signed short&>(animationStage))-2);
            break;
        }
