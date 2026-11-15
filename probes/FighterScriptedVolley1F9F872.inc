// F872 original game 0x1F9, whole 227B/65-x86, original physical fields.
// Stage2 motion3 float X facing*original mult, Y original global, owner+0x82.
// Complete father NONEXACT, no independent case exact CODE.
case 0x1F9: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && field07C==3) {
        SpawnAt453C80(0x32,
            float((facing)*50)+(x),
            (*(&y))+g_F872Volley1F9YAt006598BC,
            (facing),1);
        PrepareActionAt453D60(0x14);
        reinterpret_cast<signed short&>(opponent->field082)=0x1E;
        SetNativeActionAt40FAC0(0x1FB);
        return;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    return;
}
