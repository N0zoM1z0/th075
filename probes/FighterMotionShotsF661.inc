// F661: actual original fighter 00543210 native shot cases 0x18A/0x18B.
// Full parent ordinary VC7.1 C++ source grammar, still NONSTRICT.
// FILD scratch operands remain genuinely nonexact against original native
// EBP-0x88 and EBP-0x8C. Do NOT credit either as strict native interior.
        case 0x18A: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                velocityX=15.0f;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
            if ((velocityX)<g_ThresholdAt0065782C) {
                velocityX=0.0f;
                field3AC=0;
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                SpawnFloatXYAt453A70(0x327,
                    float(facing*151)+(x),
                    (y)+g_YPlusAt0065929C,
                    facing,1);
            }
            break;
        }
        case 0x18B: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                velocityX=10.0f;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>6) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(2);
            if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                SetAuxActionAt40FB40(6);
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                SpawnFloatXYAt453A70(0x328,
                    float(facing*128)+(x),
                    (y)+g_YPlusAt00658400,
                    facing,1);
            }
            break;
        }
