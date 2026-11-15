// F721: original complete native action 2E5 (0054F241..0054F55F):
// 798 original CODE B /223 x86. Genuine seven-argument projectile,
// original random direction/facing and stage-count based shots.
// Native original whole giant remains NONEXACT; no individual case credit.
        case 0x2E5: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                field07C=1;
                ResetAt453E20();
                SpawnSevenAt453B50(0x38E,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1,0,1);
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(RandomBoundaryAt455580(60,80)
                   -static_cast<int>(g_CloudOpponentAt006714D0)*20);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0)
                PrepareActionAt453D40(9);
            if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if (opponent->y==g_ThresholdAt0065782C)
                    reinterpret_cast<signed short&>(scriptCounterF00)=0;
                else
                    reinterpret_cast<signed short&>(scriptCounterF00)=20;
                if (RandomBoundaryAt455580(0,100)<20) {
                    if (RandomBoundaryAt455580(0,100)<50)
                        reinterpret_cast<signed short&>(scriptCounterF00)=0;
                    else
                        reinterpret_cast<signed short&>(scriptCounterF00)=20;
                }
                field314=static_cast<float>(reinterpret_cast<signed short&>(scriptCounterF00));
                SpawnFloatXYAt453A70(0x386,
                    float(facing*65)+(x),
                    (*(&y))+g_BarrageY1At006591EC,
                    facing,1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0
                && (reinterpret_cast<signed short&>(scriptCounterF02))<(3-static_cast<int>(g_CloudOpponentAt006714D0))*2) {
                ++reinterpret_cast<signed short&>(scriptCounterF02);
                SetAuxActionAt40FB40(9);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==12 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                field314=static_cast<float>(reinterpret_cast<signed short&>(scriptCounterF00));
                if ((reinterpret_cast<signed short&>(scriptCounterF00))==0)
                    SpawnFloatXYAt453A70(0x384,
                        float(facing*65)+(x),
                        (*(&y))+g_BarrageY1At006591EC,
                        facing,1);
                if ((reinterpret_cast<signed short&>(scriptCounterF00))==20)
                    SpawnFloatXYAt453A70(0x388,
                        float(facing*65)+(x),
                        (*(&y))+g_BarrageY1At006591EC,
                        facing,1);
                PrepareActionAt453D40(10);
            }
            break;
        }
