// F625 complete original 0043B0B0 248B/75-x86 authored SceneObject
// virtual destructor native-lifetime control. This direct-release
// alternative restores native texture/delete EBP slots but emits
// only 230B/69-x86; it remains explicitly NONEXACT whole function.
// F589: strictly NONEXACT original SceneObject virtual destructor probe.
// Pinned Japanese TH075 1.11 0043B0B0 has 248 native CODE bytes and
// 75 original x86 instructions, 12 genuine typed COFF fields.
// Actual original temp EBP allocation differs from VC7.1 source.
// Source-only texture delete expression probes: never count as exact.
#include <stdlib.h>
// This receiver reuses native-observed 8-byte scene base boundary.
// It does not assert the original scene's nominal size or layout.
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
BattleSceneF200::~BattleSceneF200()
{
    if (g_FrameClockModeAt0066C238 == 2 || 4)
        StateValueF200::SetClampedGameValue(16);
    if (FIELD(TextureManagerF200*,0x08))
        delete FIELD(TextureManagerF200*,0x08);
    if (FIELD(void*,0x4c)) {
        // Direct native resource release without a named pointer.
        free(FIELD(void*,0x4c));
    }
    if (FIELD(void*,0x50)) {
        // Direct native resource release without a named pointer.
        free(FIELD(void*,0x50));
    }
    if (FIELD(void*,0x54)) {
        // Direct native resource release without a named pointer.
        free(FIELD(void*,0x54));
    }
}
#undef FIELD
