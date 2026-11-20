// F622 actual original packed action 0x62: collision counter capture and
// dispatch to three action states, in one entire incomplete fighter
// Advance() C++ TU. No whole function or subrange credit.
case 0x62: {
#if F622_CHECK_DIRECTION
    if ((facing)*inputX>0) {
        // The original PE has JA *into* the store for each of the
        // first three uint fields and JBE *around* it on the fourth.
        // This is a four-way OR, not three-zero AND one-positive.
        if (static_cast<unsigned int>(inputA)>0 ||
            static_cast<unsigned int>(inputB)>0 ||
            static_cast<unsigned int>(inputC)>0 ||
            static_cast<unsigned int>(inputD)>0)
            scriptCounterF00=1;
    }
    if ((facing)*inputX<0) {
        // The original PE has JA *into* the store for each of the
        // first three uint fields and JBE *around* it on the fourth.
        // This is a four-way OR, not three-zero AND one-positive.
        if (static_cast<unsigned int>(inputA)>0 ||
            static_cast<unsigned int>(inputB)>0 ||
            static_cast<unsigned int>(inputC)>0 ||
            static_cast<unsigned int>(inputD)>0)
            scriptCounterF00=2;
    }
#endif
    if (AdvanceNestedFrame()==field070) {
        ResetPrimaryCounters(0x5F);
        if (scriptCounterF00==1)
            ResetPrimaryCounters(0x5D);
        if (scriptCounterF00==2)
            ResetPrimaryCounters(0x5E);
    }
    break;
}
