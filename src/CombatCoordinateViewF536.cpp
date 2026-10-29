// F536: complete original 00455770..004557DE (111 native CODE bytes).
// The original receives two float arguments (thiscall, RET 8). Its borrowed
// receiver contains four observed float fields at +0x2D8..+0x2E4. No complete
// source class layout, original C++ identifier, or live call graph is assumed.
// Raw, unparenthesized FIELD is intentional: VC7.1 evaluates these native
// field lvalues before the x87 operands. Parenthesizing the macro changes
// instruction order and the subtraction of the first incoming coordinate.
class CombatCoordinateViewF536 {
public:
    void MapWorldToScreen(float x, float y);
};

extern float g_CombatOutputXAt006714A8;
extern float g_CombatOutputYAt0067142C;
extern float g_CombatScaleXAt00657884;
extern float g_CombatScaleYAt00657D10;

#define FIELD(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))

void CombatCoordinateViewF536::MapWorldToScreen(float x, float y) {
    float width = FIELD(0x2DC) - FIELD(0x2D8);
    float height = FIELD(0x2E0) - FIELD(0x2E4);
    g_CombatOutputXAt006714A8 = (x - FIELD(0x2D8)) / width * g_CombatScaleXAt00657884;
    g_CombatOutputYAt0067142C = (FIELD(0x2E0) - y) / height * g_CombatScaleYAt00657D10;
}

#undef FIELD
