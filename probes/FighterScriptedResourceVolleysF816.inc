// F816: original Japanese TH075 scripted fighter 005214B0 actions
// 0x60 and 0x61 are each 586 complete native interior CODE B /169 x86,
// not separate callable original functions. Real original signed contact
// threshold is strict <, both ground resets use auxiliary action 4,
// and stage-four continuation is inside the getter-negative else body.
// Real native game cases each exit DIRECTLY to the encompassing
// function epilogue: their ordinary C++ return is semantically correct
// because the enclosing original switch has no further work afterward.
// Each ten-projectile loop's index is used by real original gameplay;
// it naturally restores the native EBP-0x10 saved this in its full parent.
        case 0x60: {
            if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66)) * I32(0x4DC)>0
                && (static_cast<unsigned int>(I32(0x4E8))>0
                 || static_cast<unsigned int>(I32(0x4EC))>0
                 || static_cast<unsigned int>(I32(0x4F0))>0
                 || static_cast<unsigned int>(I32(0x4F4))>0))
                S16(0xF00)=1;
            if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66)) * I32(0x4DC)<0
                && (static_cast<unsigned int>(I32(0x4E8))>0
                 || static_cast<unsigned int>(I32(0x4EC))>0
                 || static_cast<unsigned int>(I32(0x4F0))>0
                 || static_cast<unsigned int>(I32(0x4F4))>0))
                S16(0xF00)=2;
            if (S16(0x62)==0 && S16(0x64)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
                if (S16(0xEFA)>25) {
                    S16(0xEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
                }
            }
            if (S16(0x62)==3 || S16(0x62)==2) {
                POS54=POS54-POS5C;
                if (POS54+POS48<g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(4);
                    return;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0x62);
                if (U8(0x3CF)==0)
                    SetNativeActionAt40FAC0(0x63);
            } else {
                if (S16(0x62)==2 && S16(0x64)==0) {
                    POS=static_cast<float>(static_cast<int>(S16(0xF00)))*g_F748_SpeedScaleAt006590B8;
                    POS54=static_cast<float>(-static_cast<int>(S16(0xF02)))*g_F748_SpeedScaleAt006590B8;
                    POS5C=2.0f;
                }
                if (S16(0x62)==4 && S16(0x64)==0)
                    SetAuxActionAt40FB40(3);
            }
            return;
        }

        case 0x61: {
            if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66)) * I32(0x4DC)>0
                && (static_cast<unsigned int>(I32(0x4E8))>0
                 || static_cast<unsigned int>(I32(0x4EC))>0
                 || static_cast<unsigned int>(I32(0x4F0))>0
                 || static_cast<unsigned int>(I32(0x4F4))>0))
                S16(0xF00)=1;
            if (static_cast<int>(*reinterpret_cast<signed char*>(RAW+0x66)) * I32(0x4DC)<0
                && (static_cast<unsigned int>(I32(0x4E8))>0
                 || static_cast<unsigned int>(I32(0x4EC))>0
                 || static_cast<unsigned int>(I32(0x4F0))>0
                 || static_cast<unsigned int>(I32(0x4F4))>0))
                S16(0xF00)=2;
            if (S16(0x62)==0 && S16(0x64)==0) {
                for (int shot=0;shot<10;++shot)
                    SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
                if (S16(0xEFA)>25) {
                    S16(0xEFA)=0;
                    SpawnDirectedAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
                }
            }
            if (S16(0x62)==3 || S16(0x62)==2) {
                POS54=POS54-POS5C;
                if (POS54+POS48<g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(4);
                    return;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0x62);
                if (U8(0x3CF)==0)
                    SetNativeActionAt40FAC0(0x63);
            } else {
                if (S16(0x62)==2 && S16(0x64)==0) {
                    POS=static_cast<float>(static_cast<int>(S16(0xF00)))*g_F748_SpeedScaleAt006590B8;
                    POS54=static_cast<float>(-static_cast<int>(S16(0xF02)))*g_F748_SpeedScaleAt006590B8;
                    POS5C=2.0f;
                }
                if (S16(0x62)==4 && S16(0x64)==0)
                    SetAuxActionAt40FB40(3);
            }
            return;
        }
