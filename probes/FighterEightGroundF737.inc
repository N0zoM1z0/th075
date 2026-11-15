// F737: two entire native grounded eight-shot actions in the true
// 00543210 giant. Original 194 = 0054967C..005497CB (335 B/92 x86),
// 195 = 005497CB..0054991A (335 B/92 x86). These are action bodies,
// NOT standalone original game functions or accepted exact CODE.
        case 0x194: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0)
                field07C=1;
            velocityY=velocityY-field05C;
            if ((y+velocityY)<=g_ThresholdAt0065782C) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(0);
                velocityX=-4.0f;
                velocityY=9.0f;
                field05C=0.65f;
                field314=0.0f;
                StartAnimationAt46D000(200);
                for (int shot=0;shot<8;++shot) {
                    SpawnFloatXYAt453A70(0x324,
                       float(facing*35)+(x),
                       (*(&y))+g_F737_RoundY0At00659A24,
                       facing,1);
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetNativeActionAt40FAC0(9);
            break;
        }
        case 0x195: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0)
                field07C=1;
            velocityY=velocityY-field05C;
            if ((y+velocityY)<=g_ThresholdAt0065782C) {
                velocityY=0.0f;
                velocityX=0.0f;
                y=0.0f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(0);
                velocityX=-4.0f;
                velocityY=9.0f;
                field05C=0.65f;
                field314=-30.0f;
                StartAnimationAt46D000(200);
                for (int shot=0;shot<8;++shot) {
                    SpawnFloatXYAt453A70(0x324,
                       float(facing*27)+(x),
                       (*(&y))+g_F737_RoundY1At00659A20,
                       facing,1);
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetNativeActionAt40FAC0(9);
            break;
        }
