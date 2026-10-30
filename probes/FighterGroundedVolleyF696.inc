// F696: real action 0x2FB in the original 00543210 whole fighter parent.
// Native extent 00550D97..0055101E: 181 x86 instructions / 647 CODE bytes.
// Native ground contact, one angled 391 projectile, a real indexed 392
// volley, and completion/phase transitions. Whole parent is NOT exact.
        case 0x2FB: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                S16(0xF02)=0;
                S16(0xF04)=0;
                POS=15.0f;
                POS54=10.0f;
                POS5C=0.3f;
            }
            if (S16(0x62)<18) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0x12);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (S16(0x62)==11 && S16(0x64)==0) {
                PrepareActionAt453D40(0x12);
                F32(0x314)=CalculateAngleAt483300(
                    (*reinterpret_cast<float*>(OWNER+0x48))-POS48,
                    ((*reinterpret_cast<float*>(OWNER+0x44))-F32(0x44))
                        *static_cast<float>(*reinterpret_cast<signed char*>(RAW+0x66)))
                    /g_StormAngleDenominatorAt00657828;
                SpawnFloatXYAt453A70(0x391,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*30)+F32(0x44),
                    (*(&POS48))+g_StormAngleShotYAt00659A18,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                for (int i=0;i<static_cast<int>(g_CloudOpponentAt006714D0)*2+2;++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(*reinterpret_cast<signed char*>(RAW+0x66)*36)+F32(0x44),
                        (*(&POS48))+g_StormYAt0065948C,
                        *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==13 && S16(0x64)==0 &&
                S16(0xF00)<static_cast<int>(g_CloudOpponentAt006714D0)+3) {
                SetAuxActionAt40FB40(0xB);
                ++S16(0xF00);
            }
            if (S16(0x62)==18 && S16(0x64)==0)
                SetAuxActionAt40FB40(0x10);
            break;
        }
