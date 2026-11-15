// F768: real borrowed actor +0x44 float position restores native 2F8
// FILD then FSUBR grammar. 166 genuine nonfield register bytes remain
// NONEXACT; original entire 58KB parent still unaccepted.
// F681: authentic original fighter 2F8 928B/252-x86 source grammar.
// This native case remains NONSTRICT: source emits 904B, real local EBP
// slots, one x87 FILD/FSUBR sequence and GPR phase differ from PE.
// The meaningful real stage6 counter loop shifts source saved-this
// from EBP-8 to EBP-0xC. No fake locals, manual code or credit.
        case 0x2F8: {
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                reinterpret_cast<signed short&>(fieldF04)=0;
                field07C=1;
                ResetAt453E20();
            }
            if ((reinterpret_cast<signed short&>(animationStage))==2) {
                ++reinterpret_cast<signed short&>(scriptCounterF02);
                if ((reinterpret_cast<signed short&>(scriptCounterF02))>4) {
                    SpawnAt453C80(0x40,
                        reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float(facing*3),
                        (*(&y))+g_YPlusAt0065929C,1,1);
                    reinterpret_cast<signed short&>(scriptCounterF02)=0;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
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
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(60,100)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D40(0x15);
            if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    SetAuxActionAt40FB40(2);
                    break;
                }
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    SetAuxActionAt40FB40(3);
                    break;
                }
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0
                && (reinterpret_cast<signed short&>(scriptCounterF00))<static_cast<int>(g_CloudOpponentAt006714D0)+6) {
                SetAuxActionAt40FB40(6);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0
                && (reinterpret_cast<signed short&>(scriptCounterF00))<10-static_cast<int>(g_CloudOpponentAt006714D0)) {
                SetAuxActionAt40FB40(8);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            break;
        }
