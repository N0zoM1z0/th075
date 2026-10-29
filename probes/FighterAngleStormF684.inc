// F684: 00543210 original complete 0x2F9 angle-storm source grammar.
// Native 381 genuine x86 /1367 original CODE B /34 actual PE/COFF fields.
// Compiled 381 x86/1319B, 16 original wide EBP integer float temporaries
// and original GPR register roles remain NONSTRICT. Never credit case.
// CalculateAngleAt483300 / __ftol2 are native source ABI probes only.
case 0x2F9: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                S16(0xF04)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)>1 && S16(0x62)<20) {
                if (S16(0x62)>15 || S16(0x62)<10) {
                    POS54=POS54-POS5C;
                }
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0x14);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (S16(0x62)==11 && S16(0x64)==0) {
                PrepareActionAt453D40(0x12);
                F32(0x314)=float(S16(0xF02)+S16(0xF00)*10);
                SpawnFloatXYAt453A70(0x391,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*30)+F32(0x44),
                    (*(&POS48))+g_StormAngleShotYAt00659A18,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                for (int i=0;i<static_cast<int>(g_CloudOpponentAt006714D0)*2+4;++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*30)+F32(0x44),
                        (*(&POS48))+g_StormAngleShotYAt00659A18,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==14 && S16(0x64)==0) {
                PrepareActionAt453D40(0x12);
                F32(0x314)=float(S16(0xF02)-S16(0xF00)*10);
                SpawnFloatXYAt453A70(0x391,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*30)+F32(0x44),
                    (*(&POS48))+g_StormAngleShotYAt00659A18,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                for (int i=0;i<static_cast<int>(g_CloudOpponentAt006714D0)*2+4;++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*30)+F32(0x44),
                        (*(&POS48))+g_StormAngleShotYAt00659A18,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0x516)=RandomBoundaryAt455580(60,100)
                       -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if (S16(0x62)==2 && S16(0x64)==0) {
                POS54=12.5f;
                POS=-8.0f;
                POS5C=0.4f;
            }
            if (S16(0x62)==10 && S16(0x64)==0) {
                POS=(*(&POS))*g_StormMotionAt00658348;
                POS54=(*(&POS54))*g_StormMotionAt00658348;
            }
            if (S16(0x62)==11 && S16(0x64)==0) {
                S16(0xF02)=static_cast<short>(
                    CalculateAngleAt483300(
                        (*reinterpret_cast<float*>(OWNER+0x48))-POS48,
                        ((*reinterpret_cast<float*>(OWNER+0x44))-F32(0x44))
                           *static_cast<float>(*reinterpret_cast<signed char*>(RAW+0x66)))
                    /g_StormAngleDenominatorAt00657828);
            }
            if (S16(0x62)==13 && S16(0x64)==0) {
                if (S16(0xF00)<static_cast<int>(g_CloudOpponentAt006714D0)*2+1) {
                    SetAuxActionAt40FB40(0xB);
                    ++S16(0xF00);
                } else S16(0xF00)=0;
            }
            if (S16(0x62)==14 && S16(0x64)==0) {
                S16(0xF02)=static_cast<short>(
                    CalculateAngleAt483300(
                        (*reinterpret_cast<float*>(OWNER+0x48))-POS48,
                        ((*reinterpret_cast<float*>(OWNER+0x44))-F32(0x44))
                           *static_cast<float>(*reinterpret_cast<signed char*>(RAW+0x66)))
                    /g_StormAngleDenominatorAt00657828);
            }
            if (S16(0x62)==16 && S16(0x64)==0
                && S16(0xF00)<static_cast<int>(g_CloudOpponentAt006714D0)*2+1) {
                SetAuxActionAt40FB40(14);
                ++S16(0xF00);
            }
            if (S16(0x62)==20 && S16(0x64)==0) SetAuxActionAt40FB40(0x12);
            break;
        }
