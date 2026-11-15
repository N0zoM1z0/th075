// F656: physical original native 0x131 ground/recovery stages in nonexact giant 00543210.
        case 0x131: {
            velocityY=velocityY-field05C;
            if (y+velocityY<=g_ThresholdAt0065782C) {
                SetNativeActionAt40FAC0(10);
                y=0.0f;
                field05C=0.0f;
                velocityY=0.0f;
                break;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(9);
            if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1C);
            if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1D);
            break;
        }
