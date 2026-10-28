// F363: original character special-effect policy with distance threshold
// checks before the action-window effect spawns (unlike F062/F361).
// Native effect 850, +0xF0C distance counter and 1.0f scale are specific
// to this 1,028-byte original body, not assumptions from a shared class.
// Declaration-only receiver view; complete owner layout unknown.
class CharacterAux00555530F363 {
public:
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
};


#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))

// Names are provisional. Only these field accesses and receiver ABI are observed.
void CharacterAux00555530F363::AdvanceAuxiliary() {
    if (FLOAT(0x50) == 0.0f && FIELD(signed char, 0x3AC) > 0) {
        FIELD(signed char, 0x3AC) = 0;
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 540.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -540.0f) {
        FIELD(short, 0xF0C) = 60;
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 320.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -320.0f) {
        FIELD(short, 0xF0C) = FIELD(short, 0xF0C) + 1;
        if (FIELD(short, 0xF0C) > 60) FIELD(short, 0xF0C) = 60;
    }
    else {
        FIELD(short, 0xF0C) = 0;
    }
    if (FIELD(short, 0xF0A) != 1) {
        if (FIELD(short, 0x60) > 149 && FIELD(short, 0x60) < 154) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 1.0f;
            FLOAT(0x300) = 1.0f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(850, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 94.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
        if (FIELD(short, 0x60) > 153 && FIELD(short, 0x60) < 158) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 1.0f;
            FLOAT(0x300) = 1.0f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(850, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 60.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
        if (FIELD(short, 0x60) == 158) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 1.0f;
            FLOAT(0x300) = 1.0f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(850, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 100.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    }

}

#undef OPPONENT_FLOAT
#undef FLOAT
#undef FIELD
