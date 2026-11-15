// F671: native original 00543210 action 0x258 four-shot barrage C++.
// This entire original case has 134 authentic x86 and 12 true PE fields,
// but is deliberately NONSTRICT: four original EBP integer-to-float
// conversion scratch pairs -0x114..-0x120 compile at -0x2C..-0x38.
// This is not whole-giant or native-inner-case strict acceptance.
case 0x258: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                field07C=1;
                ResetAt453E20();
            }
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                StartAnimationAt46D000(100);
                field314=-110.0f;
                field318=5.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(facing*40)+(x),
                    (*(&y))+g_BarrageY1At006591EC,
                    facing,1);
                field314=110.0f;
                field318=5.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(facing*40)+(x),
                    (*(&y))+g_BarrageY2At006581DC,
                    facing,1);
                field314=-70.0f;
                field318=4.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_BarrageY3At0065908C,
                    facing,1);
                field314=70.0f;
                field318=4.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(facing*75)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
            break;
        }
