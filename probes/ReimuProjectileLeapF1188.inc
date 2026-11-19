case R1188_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f; velocityY=0.0f; field05C=0.0f;
        field080=1; field07C=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        velocityX=(velocityX)-g_ReimuLeapDragAt006583FC;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f;
            SetAuxActionAt40FB40(10);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==4 && (animationFrame)==0) {
        SpawnDirectedAt453A70(0x32D,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),reinterpret_cast<char&>(facing),1);
        PlaySound(3);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=R1188_LEAP_X; velocityY=R1188_LEAP_Y; field05C=0.9f;
        SpawnRawXYAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),reinterpret_cast<char&>(facing),1);
    }
    if ((animationStage)==10 && (animationFrame)==0) SetAuxActionAt40FB40(8);
    break;
}
