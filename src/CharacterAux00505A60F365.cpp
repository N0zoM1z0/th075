// F365: independently checked COMPLETE native 1,576-byte extended character special effect
// controller. Like the already exact F062, this uses the same inherited
// effect-spawner ABI, but its effect 817, scale 1.0f, linked flag one and
// +0xF12 distance counter are independently verified for THIS target.
// The original computes signed angular timers, a true signed comparison
// direction, directional random projectiles and three linked effects. The
// compiler register state at the F0E timer depends on authentic compound
// += (not a semantically equivalent ordinary assignment). The direction
// boolean is naturally inlined, not stored in an invented helper local.
// Declaration-only receiver view: full original fighter layout is unknown.
class CharacterAux00505A60F365 {
public:
    void UpdateAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    int Rand(int,int);
    void SpawnProjectile(int,float,float,unsigned char,int);
};


#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x2E8))+(offset)))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))

extern const float g_SpecialPowerStepAt006590B4;
// Names are provisional. Only these field accesses and receiver ABI are observed.
void CharacterAux00505A60F365::UpdateAuxiliary() {
    if (FLOAT(0x50) == 0.0f && FIELD(signed char, 0x3AC) > 0) {
        FIELD(signed char, 0x3AC) = 0;
    }
    if (FIELD(short, 0x3B8) == 0)
        FIELD(short, 0xF0E) += FIELD(signed char, 0x66) * 5;
    if (FIELD(short, 0xF0E) < 0) FIELD(short, 0xF0E) = 359;
    if (FIELD(short, 0xF0E) >= 360) FIELD(short, 0xF0E) = 0;
    if (FIELD(short, 0x3B8) == 0)
        FIELD(short, 0xF0C) = FIELD(short, 0xF0C) + 2;
    if (FIELD(short, 0xF0C) < 0) FIELD(short, 0xF0C) = 359;
    if (FIELD(short, 0xF0C) >= 360) FIELD(short, 0xF0C) = 0;
    if (FIELD(short, 0xF10) > 0) {
        FLOAT(0x490) = float(FIELD(short,0xF10)+20) * g_SpecialPowerStepAt006590B4 * float(FIELD(signed char,0x66)*OPPONENT_FIELD(signed char,0x66)) * float(int(((OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char,0x66) > 0.0f))*2-1);
        FIELD(short,0xF10) = FIELD(short,0xF10)-2;
        if (Rand(0,100)<50)
            SpawnProjectile(0x38c, float(Rand(0,640)*FIELD(signed char,0x66))+FLOAT(0x44),0.0f,FIELD(unsigned char,0x66),1);
        else
            SpawnProjectile(0x38c, FLOAT(0x44)-float(Rand(0,640)*FIELD(signed char,0x66)),0.0f,-FIELD(signed char,0x66),1);
        if (FIELD(short,0xF10)<0) FIELD(short,0xF10)=0;
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
            SpawnTrackedEffect(817, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 94.0f, FIELD(signed char, 0x66), 1, 1);
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
            SpawnTrackedEffect(817, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 60.0f, FIELD(signed char, 0x66), 1, 1);
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
            SpawnTrackedEffect(817, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 100.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 540.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -540.0f) {
        FIELD(short, 0xF12) = 60;
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 320.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -320.0f) {
        FIELD(short, 0xF12) = FIELD(short, 0xF12) + 1;
        if (FIELD(short, 0xF12) > 60) FIELD(short, 0xF12) = 60;
    }
    else {
        FIELD(short, 0xF12) = 0;
    }
}

#undef OPPONENT_FIELD
#undef OPPONENT_FLOAT
#undef FLOAT
#undef FIELD
