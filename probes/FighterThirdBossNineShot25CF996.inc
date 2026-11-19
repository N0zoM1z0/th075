// F996 native Japanese TH075 original 004AC040 state25C.
 // Real original PE 004B9327..004B973A: 1043 CODE B /271 x86,
 // 23 original typed PE external fields, nine genuine sprite342
 // shots with angles -28,-21,-14,-7,0,+7,+14,+21,+28.
 // All original mnemonic/width roles match normal VC7.1 source,
 // 162 GPR positions differ, whole 82KB original NONEXACT.
// F996 original Japanese fighter 004AC040 native action25C.
case 0x25C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(0);
        UpdateGaugeTimer(0xFA);
        field314=-28.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=-21.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=-14.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=-7.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=0.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=7.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=14.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=21.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
        field314=28.0f;
        field318=10.0f;
        SpawnFloatXYAt453A70(0x342,
            float((facing)*49)+(x),
            (*(&y))+g_F968_RoundY190At00659294,
            facing,1);
    }
    break;
}
