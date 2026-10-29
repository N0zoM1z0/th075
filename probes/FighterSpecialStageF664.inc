// F664 original selected giant 00543210: full physical native action 0x200/0x201.
// Ordinary VC7.1 C++ native source interiors; enclosing whole giant remains
// NONEXACT, and SpawnRawXYAt453C80 is a provisional raw-argument ABI proxy.
// Original position +0x44/+0x48 is passed as DWORD bits, never implicit
// FLD/FSTP by-value float conversions in this source grammar.
        case 0x200: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)>7) {
                POS=POS-g_FallingLateDragAt00659240;
                if (POS<g_ThresholdAt0065782C) POS=0.0f;
            }
            if (S16(0x62)==7 && I32(0x7C)==2) {
                SetAuxActionAt40FB40(8);
                POS=10.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0) {
                PrepareActionAt453D40(7);
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==7 && S16(0x64)==0) POS=50.0f;
            if (S16(0x62)==8 && S16(0x64)==0) POS=10.0f;

            break;
        }
        case 0x201: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                FLAG=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)>7) {
                POS=POS-g_FallingLateDragAt00659240;
                if (POS<g_ThresholdAt0065782C) POS=0.0f;
            }
            if (S16(0x62)==7 && I32(0x7C)==2) {
                SetAuxActionAt40FB40(8);
                POS=10.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0) {
                PrepareActionAt453D40(7);
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==7 && S16(0x64)==0) POS=50.0f;
            if (S16(0x62)==8 && S16(0x64)==0) POS=10.0f;
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)==0) {
                ++S16(0xF00);
                SetAuxActionAt40FB40(2);
                I32(0x7C)=0;
                S16(0x80)=1;
            }
            break;
        }
