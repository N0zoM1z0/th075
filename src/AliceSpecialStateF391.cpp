// Independently original R068-authored 256-byte Alice fighter special-state leaf.
// Only borrowed field ABIs are modeled, no full fighter/parent class layout.
class AliceFighterUpdateF391 {public:void UpdateSpecialState();};
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))
void AliceFighterUpdateF391::UpdateSpecialState() {
    if (FLOAT(0x50) == 0.0f && FIELD(signed char, 0x3AC) > 0) {
        FIELD(signed char, 0x3AC) = 0;
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 540.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -540.0f) {
        FIELD(short, 0xF14) = 60;
    }
    if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > 320.0f || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < -320.0f) {
        FIELD(short, 0xF14) = FIELD(short, 0xF14) + 1;
        if (FIELD(short, 0xF14) > 60) FIELD(short, 0xF14) = 60;
    }
    else {
        FIELD(short, 0xF14) = 0;
    }
}
#undef OPPONENT_FLOAT
#undef FLOAT
#undef FIELD
