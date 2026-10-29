// F656: physical original native 0x131 ground/recovery stages in nonexact giant 00543210.
        case 0x131: {
            POS54=POS54-POS5C;
            if (POS48+POS54<=g_ThresholdAt0065782C) {
                SetNativeActionAt40FAC0(10);
                POS48=0.0f;
                POS5C=0.0f;
                POS54=0.0f;
                break;
            }
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
            if (S16(0x62)==3 && S16(0x64)==0) PrepareActionAt453D60(0x1C);
            if (S16(0x62)==5 && S16(0x64)==0) {
                S16(0x80)=1;
                I32(0x7C)=0;
            }
            if (S16(0x62)==6 && S16(0x64)==0) PrepareActionAt453D60(0x1D);
            break;
        }
