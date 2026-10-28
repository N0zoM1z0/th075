// Borrowed fighter receiver and effect spawner ABI; the complete fighter class
// (including parent/derived layouts) is not instantiated or asserted here.
// The two field-access macro expressions intentionally retain the exact form
// of independently cold-exact F062 CharacterAux5E5500: VC7.1 selects a
// different x87 comparison evaluation order for a superficially equivalent
// nested FIELD(float,...) macro, although the C++ lvalue is identical.
// The step/threshold and Yukari-only counters here are native independently
// verified, not copied from F062.
class YukariSpecialF345 {
public:
    void UpdateSpecialState();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
};
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))

void YukariSpecialF345::UpdateSpecialState() {
    if (FIELD(short, 0x3B8) == 0)
        FIELD(short, 0xF12) = FIELD(short, 0xF12) + 2;
    if (FIELD(short, 0xF12) >= 180)
        FIELD(short, 0xF12) = -180;
    if (FLOAT(0x50) == 0.0f && FIELD(signed char, 0x3AC) > 0)
        FIELD(signed char, 0x3AC) = 0;
    if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xF0A) == 0) {
        if (FIELD(short, 0x60) > 149 && FIELD(short, 0x60) < 154) {
            SpawnTrackedEffect(830, FIELD(signed char, 0x66)*57 + FLOAT(0x44), FLOAT(0x48) + 94.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
        if (FIELD(short, 0x60) > 153 && FIELD(short, 0x60) < 158) {
            SpawnTrackedEffect(830, FIELD(signed char, 0x66)*57 + FLOAT(0x44), FLOAT(0x48) + 60.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
        if (FIELD(short, 0x60) == 158) {
            SpawnTrackedEffect(830, FIELD(signed char, 0x66)*57 + FLOAT(0x44), FLOAT(0x48) + 100.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    }
    if (FLOAT(0x44)-OPPONENT_FLOAT(0x44) > 540.0f || FLOAT(0x44)-OPPONENT_FLOAT(0x44) < -540.0f)
        FIELD(short, 0xF32)=60;
    if (FLOAT(0x44)-OPPONENT_FLOAT(0x44) > 320.0f || FLOAT(0x44)-OPPONENT_FLOAT(0x44) < -320.0f) {
        FIELD(short, 0xF32)=FIELD(short, 0xF32)+1;
        if (FIELD(short, 0xF32)>60) FIELD(short, 0xF32)=60;
    } else {
        FIELD(short, 0xF32)=0;
    }
}
#undef OPPONENT_FLOAT
#undef FLOAT
#undef FIELD
