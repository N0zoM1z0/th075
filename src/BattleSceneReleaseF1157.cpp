#include <new>

// Pointer-only views of the original three trivially destroyed HUD objects.
// No allocation, embedding or complete private object size is inferred here.
class DigitAtlasReleaseF1157 {};
class ComboCounterReleaseF1157 {};

// The vptr and shared-client word occupy the observed eight-byte base boundary.
class SceneBaseF200 {
    unsigned int sourceGlobalAt4;
public:
    SceneBaseF200();
    virtual ~SceneBaseF200();
};
class TextureManagerF200 { public: ~TextureManagerF200(); };
extern signed char g_FrameClockModeAt0066C238;
namespace StateValueF200 { void __cdecl SetClampedGameValue(int); }
class BattleSceneF200: public SceneBaseF200 {
public:
    BattleSceneF200();
    virtual ~BattleSceneF200();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))

BattleSceneF200::~BattleSceneF200() {
    // Preserve the original literal nonzero second operand and its native test.
    if (g_FrameClockModeAt0066C238 == 2 || 4)
        StateValueF200::SetClampedGameValue(16);
    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);
    if (FIELD(DigitAtlasReleaseF1157*,0x4c))
        delete FIELD(DigitAtlasReleaseF1157*,0x4c);
    if (FIELD(ComboCounterReleaseF1157*,0x50))
        delete FIELD(ComboCounterReleaseF1157*,0x50);
    if (FIELD(ComboCounterReleaseF1157*,0x54))
        delete FIELD(ComboCounterReleaseF1157*,0x54);
}
#undef FIELD
