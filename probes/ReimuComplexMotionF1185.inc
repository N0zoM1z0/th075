// Native Reimu CC/CD/CE motion loop. Parameters are actual actor policies;
// this source is included only by the live nonexact 0045DD70 parent.
case R1185_ACTION: {
    if ((*(&y)==g_ThresholdAt0065782C) || velocityY>g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
        reinterpret_cast<signed short&>(field088)=2;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (field3AC)==0) ResetAt453E20();
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(10);
            y=0.0f;
            ResetAt453E20();
            break;
        }
    }
#if R1185_HAS_AUX
    if ((reinterpret_cast<signed short&>(animationStage))==4 && velocityY<g_ExtraThresholdAt00657D14) SetAuxActionAt40FB40(5);
#endif
    ++reinterpret_cast<signed short&>(animationFrame);
    if ((reinterpret_cast<signed short&>(animationFrame))>=(reinterpret_cast<signed short&>(field072))) {
        reinterpret_cast<signed short&>(animationFrame)=0;
        ++reinterpret_cast<signed short&>(animationStage);
        if ((reinterpret_cast<signed short&>(animationStage))==2) {
            velocityX=R1185_X_SPEED;
            velocityY=R1185_Y_SPEED;
            field05C=0.65f;
            field3AC=0;
            SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        if ((reinterpret_cast<signed short&>(animationStage))>=(reinterpret_cast<signed short&>(field070))) reinterpret_cast<signed short&>(animationStage)=(reinterpret_cast<signed short&>(animationStage))-2;
        BindAnimation();
    }
    break;
}
