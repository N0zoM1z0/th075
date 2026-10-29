// F656: true original native 0x133..0x136 stage-specific movement and shots.
        case 0x133: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                POS=0.0f;
                POS54=0.0f;
                POS5C=0.0f;
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (POS>g_ThresholdAt0065782C)
                POS=POS-g_NewDragAt006581E0;
            if (POS<g_ThresholdAt0065782C) POS=0.0f;
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==3 && S16(0x64)==0) {
                PrepareActionAt453D60(0x1C);
                SpawnDirectedAt453A70(0x341,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==6 && S16(0x64)==0) POS=15.0f;
            if (S16(0x62)==8 && S16(0x64)==0) {
                PrepareActionAt453D60(0x1C);
                S16(0x80)=1;
                I32(0x7C)=0;
                SpawnDirectedAt453A70(0x342,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            break;
        }
        case 0x134: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                if (FLAG==0) ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (FLAG>0) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0xF00)=0;
            }
            if (S16(0x62)==1 && S16(0x64)==0) PrepareActionAt453D60(0x1D);
            break;
        }
        case 0x135: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                if (FLAG==0) ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (FLAG>0) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (S16(0x62)==10 || S16(0x62)==11) {
                POS=POS-g_SubtractAt00657478;
                if (POS<g_ThresholdAt0065782C) POS=0.0f;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                S16(0xF00)=0;
            }
            if (S16(0x62)==7 && S16(0x64)==0) POS=20.0f;
            if (S16(0x62)==10 && S16(0x64)==0)
                SpawnDirectedAt453A70(0x33F,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            break;
        }
        case 0x136: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                if (FLAG==0) ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (FLAG>0) {
                POS=POS-g_JumpGroundCorrectionAt00658058;
                if (POS<g_ThresholdAt0065782C) {
                    POS=0.0f;
                    FLAG=0;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==5 && S16(0x64)==0)
                SpawnDirectedAt453A70(0x33E,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            if (S16(0x62)==6 && S16(0x64)==0) PrepareActionAt453D60(0x1D);
            break;
        }
