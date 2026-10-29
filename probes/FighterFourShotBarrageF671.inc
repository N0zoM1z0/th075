// F671: native original 00543210 action 0x258 four-shot barrage C++.
// This entire original case has 134 authentic x86 and 12 true PE fields,
// but is deliberately NONSTRICT: four original EBP integer-to-float
// conversion scratch pairs -0x114..-0x120 compile at -0x2C..-0x38.
// This is not whole-giant or native-inner-case strict acceptance.
case 0x258: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                StartAnimationAt46D000(100);
                F32(0x314)=-110.0f;
                F32(0x318)=5.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x314)=110.0f;
                F32(0x318)=5.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    (*(&POS48))+g_BarrageY2At006581DC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x314)=-70.0f;
                F32(0x318)=4.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*75)+F32(0x44),
                    (*(&POS48))+g_BarrageY3At0065908C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x314)=70.0f;
                F32(0x318)=4.0f;
                SpawnFloatXYAt453A70(0x322,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*75)+F32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            break;
        }
