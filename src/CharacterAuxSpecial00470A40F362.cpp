// R049-authored complete native 1,027-byte controller at 00470A40.
// The compiled nonrelocation stream is genuinely identical to F062;
// only the three relative call displacements differ because of the
// original function address. This independent original extent receives
// distinct credit, not reuse of F062 bytes or any new callee credit.
// Declaration-only receiver view; full character owner layout unknown.
class CharacterAuxRunAt00470A40F362 {
public:
    void AdvanceAuxiliarySpecial();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
};


#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))

// Names are provisional. Only these field accesses and receiver ABI are observed.
void CharacterAuxRunAt00470A40F362::AdvanceAuxiliarySpecial() {
    if (FLOAT(0x50) == 0.0f && FIELD(signed char, 0x3AC) > 0) {
        FIELD(signed char, 0x3AC) = 0;
    }
    if (FIELD(short, 0xF0A) != 1) {
        if (FIELD(short, 0x60) > 149 && FIELD(short, 0x60) < 154) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 0.75f;
            FLOAT(0x300) = 0.75f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(998, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 94.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
        if (FIELD(short, 0x60) > 153 && FIELD(short, 0x60) < 158) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 0.75f;
            FLOAT(0x300) = 0.75f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(998, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 60.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
        if (FIELD(short, 0x60) == 158) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 0.75f;
            FLOAT(0x300) = 0.75f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(998, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 100.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 540.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -540.0f) {
        FIELD(short, 0xF2A) = 60;
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 320.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -320.0f) {
        FIELD(short, 0xF2A) = FIELD(short, 0xF2A) + 1;
        if (FIELD(short, 0xF2A) > 60) FIELD(short, 0xF2A) = 60;
    }
    else {
        FIELD(short, 0xF2A) = 0;
    }
}

#undef OPPONENT_FLOAT
#undef FLOAT
#undef FIELD
