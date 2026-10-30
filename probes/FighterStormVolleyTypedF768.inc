// F768: real borrowed actor +0x44 float position restores native 2F8
// FILD then FSUBR grammar. 166 genuine nonfield register bytes remain
// NONEXACT; original entire 58KB parent still unaccepted.
// F681: authentic original fighter 2F8 928B/252-x86 source grammar.
// This native case remains NONSTRICT: source emits 904B, real local EBP
// slots, one x87 FILD/FSUBR sequence and GPR phase differ from PE.
// The meaningful real stage6 counter loop shifts source saved-this
// from EBP-8 to EBP-0xC. No fake locals, manual code or credit.
        case 0x2F8: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                S16(0xF04)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)==2) {
                ++S16(0xF02);
                if (S16(0xF02)>4) {
                    SpawnAt453C80(0x40,
                        reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*3),
                        (*(&POS48))+g_YPlusAt0065929C,1,1);
                    S16(0xF02)=0;
                }
            }
            if (S16(0x62)==6 && S16(0x64)==0) {
                PrepareActionAt453D40(0x12);
                F32(0x314)=float(RandomBoundaryAt455580(0,40)-20);
                SpawnFloatXYAt453A70(0x391,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*36)+F32(0x44),
                    (*(&POS48))+g_StormYAt0065948C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                for (int i=0; i<static_cast<int>(g_CloudOpponentAt006714D0)*2+2; ++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*36)+F32(0x44),
                        (*(&POS48))+g_StormYAt0065948C,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=RandomBoundaryAt455580(60,100)
                           -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if (S16(0x62)==2 && S16(0x64)==0) PrepareActionAt453D40(0x15);
            if (S16(0x62)==3 && S16(0x64)==0) {
                if (S16(0xF00)<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++S16(0xF00);
                    SetAuxActionAt40FB40(2);
                    break;
                }
                S16(0xF00)=0;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                if (S16(0xF00)<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++S16(0xF00);
                    SetAuxActionAt40FB40(3);
                    break;
                }
                S16(0xF00)=0;
            }
            if (S16(0x62)==8 && S16(0x64)==0
                && S16(0xF00)<static_cast<int>(g_CloudOpponentAt006714D0)+6) {
                SetAuxActionAt40FB40(6);
                ++S16(0xF00);
            }
            if (S16(0x62)==10 && S16(0x64)==0
                && S16(0xF00)<10-static_cast<int>(g_CloudOpponentAt006714D0)) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            break;
        }
