// F834 physical original 005214B0 interior action 0xC8,
 // 657 CODE B /190 x86 and 17 actual typed PE/global fields.
 // Prefix ++ on the real +0xF00 signed short naturally emits
 // original MOV CX/ADD CX,1 instead of MOVSX ECX/ADD ECX,1.
 // All 7 direct returns target the enclosing full fighter epilogue.
 // This is NOT independently callable original exact CODE.
case 0xC8: {
    ConfigureStormAt454BC0(3,4,0xFF);
    field3AC=1;
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((velocityX)>g_F834_UpperAt00657CBC) {
        velocityX=(velocityX)-g_SubtractAt00657478;
        if ((velocityX)<g_F834_LowerAt006590B0)
            velocityX=9.0f;
    }
    if (inputY<0) {
        if ((facing)*inputX>0) {
            SetNativeActionAt40FAC0(0xCD);
            return;
        }
        SetNativeActionAt40FAC0(0xCC);
        return;
    }
    if ((reinterpret_cast<signed short&>(scriptCounterF00))>0 || (animationStage)>5) {
        if ((facing)*inputX<=0) {
            SetNativeActionAt40FAC0(0xCF);
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(field070)) {
        if ((facing)*inputX>0) {
            if ((reinterpret_cast<signed short&>(scriptCounterF00))<1) {
                SetAuxActionAt40FB40(2);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                return;
            }
        }
        SetNativeActionAt40FAC0(0xCF);
        return;
    }
    if ((animationFrame)==0 &&
            (facing)*inputX<=0 &&
            (reinterpret_cast<signed short&>(scriptCounterF00))>0) {
        SetNativeActionAt40FAC0(0xCF);
        return;
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=11.5f;
        SpawnAt453C80(0x7D,
            float((facing)*80)+(x),
            (*(&y))+g_F701_VolleyYAt00658268,
            (facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_F701_VolleyYAt00658268,
            (facing),1);
    }
    if ((animationStage)==4 && (animationFrame)==0)
        PrepareActionAt453D40(15);
    if ((animationStage)==8 && (animationFrame)==0)
        PrepareActionAt453D40(16);
    return;
}
