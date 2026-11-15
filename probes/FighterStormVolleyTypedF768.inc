// F768: real borrowed actor +0x44 float position restores native 2F8
// FILD then FSUBR grammar. 166 genuine nonfield register bytes remain
// NONEXACT; original entire 58KB parent still unaccepted.
// F681: authentic original fighter 2F8 928B/252-x86 source grammar.
// This native case remains NONSTRICT: source emits 904B, real local EBP
// slots, one x87 FILD/FSUBR sequence and GPR phase differ from PE.
// The meaningful real stage6 counter loop shifts source saved-this
// from EBP-8 to EBP-0xC. No fake locals, manual code or credit.
        case 0x2F8: {
            if ((animationStage)==0 && (animationFrame)==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                fieldF04=0;
                field07C=1;
                ResetAt453E20();
            }
            if ((animationStage)==2) {
                ++reinterpret_cast<signed short&>(scriptCounterF02);
                if ((reinterpret_cast<signed short&>(scriptCounterF02))>4) {
                    SpawnAt453C80(0x40,
                        reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float(facing*3),
                        (*(&y))+g_YPlusAt0065929C,1,1);
                    reinterpret_cast<signed short&>(scriptCounterF02)=0;
                }
            }
            if ((animationStage)==6 && (animationFrame)==0) {
                PrepareActionAt453D40(0x12);
                field314=float(RandomBoundaryAt455580(0,40)-20);
                SpawnFloatXYAt453A70(0x391,
                    float(facing*36)+(x),
                    (*(&y))+g_StormYAt0065948C,
                    facing,1);
                for (int i=0; i<static_cast<int>(g_CloudOpponentAt006714D0)*2+2; ++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(facing*36)+(x),
                        (*(&y))+g_StormYAt0065948C,
                        facing,1);
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0);
                aiCardTimer=RandomBoundaryAt455580(60,100)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if ((animationStage)==2 && (animationFrame)==0) PrepareActionAt453D40(0x15);
            if ((animationStage)==3 && (animationFrame)==0) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    SetAuxActionAt40FB40(2);
                    break;
                }
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    SetAuxActionAt40FB40(3);
                    break;
                }
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)==8 && (animationFrame)==0
                && (reinterpret_cast<signed short&>(scriptCounterF00))<static_cast<int>(g_CloudOpponentAt006714D0)+6) {
                SetAuxActionAt40FB40(6);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((animationStage)==10 && (animationFrame)==0
                && (reinterpret_cast<signed short&>(scriptCounterF00))<10-static_cast<int>(g_CloudOpponentAt006714D0)) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
