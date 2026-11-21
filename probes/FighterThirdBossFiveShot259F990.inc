// F990 pinned original Japanese 004AC040 action259.
 // Native 004B7EF2..004B823F, 845B/212 x86, 15 original
 // external PE fields. Five sprite0x325 shots with signed
 // facing*100 and genuine FILD/FSUBR original X, F02*3+
 // 145/140/135/130/125 angles. Complete normal VC7.1
 // source generates all 212 native mnemonic roles, but
 // three register-dependent angle ADD widths at native
 // indices34/96/127 and 137 GPR roles remain wrong.
 // Whole original 82KB game callable NONEXACT.
case 0x259: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
                scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>4) {
        if ((scriptCounterF02)<3 && (scriptCounterF00)<=0) {
            PlaySound(0);
            field314=float((scriptCounterF02)*3+145);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                x-float((facing)*100),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+140);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                x-float((facing)*100),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+135);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                x-float((facing)*100),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+130);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                x-float((facing)*100),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            field314=float((scriptCounterF02)*3+125);
            field318=10.0f;
            SpawnBattleEffect(0x325,
                x-float((facing)*100),
                (*(&y))+g_F971_YAt00659498,
                facing,1);
            UpdateGaugeTimer(0x64);
            ++scriptCounterF02;
            scriptCounterF00=3;
        }
        --scriptCounterF00;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    break;
}
