case R1189_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --reinterpret_cast<unsigned char&>(field366);
        ResetAt453E20();
        field080=1; field07C=0; field3AC=0; reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
#if R1189_HAS_BONUS
    if ((meterCooldown)==0 && field07C==1) meter=1000;
#endif
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),(*(&y))+g_ContactProjectionAt00657888,
            reinterpret_cast<char&>(facing),1);
        PrepareActionAt453D60(0x21);
        reinterpret_cast<short&>(opponent->fieldEFA)=0;
    }
    break;
}
