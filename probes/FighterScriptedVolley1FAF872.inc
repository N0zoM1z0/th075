// F872 original game 0x1FA, whole 227B/65-x86, original physical fields.
// Stage2 motion3 float X facing*original mult, Y original global, owner+0x82.
// Complete father NONEXACT, no independent case exact CODE.
case 0x1FA: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((animationStage)==2 && field07C==3) {
        SpawnAt453C80(0x32,
            float((facing)*36)+(x),
            (*(&y))+g_F872Volley1FAYAt00659310,
            (facing),1);
        PlaySharedSound(0x14);
        opponent->field082=0x1E;
        SetNativeActionAt40FAC0(0x1FC);
        return;
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    return;
}
