#ifndef TH075_GAME_LEAF_HELPERS_HPP
#define TH075_GAME_LEAF_HELPERS_HPP

#include "Fighter.hpp"
typedef unsigned char u8;
typedef unsigned long u32;

struct Vector3 {
    u32 x;
    u32 y;
    u32 z;
};

// Pointer-only observed prefix: CopyVector reads one Vector3 at +0x0C.
// The enclosing SpriteScene size and all later fields remain unknown.
class SpriteScene {
public:
    void CopyVector(Vector3 *destination);
    static void DispatchGlobalDraw(int first, int second, int third);

    unsigned char unknown000[0x0C];
    Vector3 field00C;
};
typedef char SpriteSceneVectorOffsetCheck[(offsetof(SpriteScene, field00C) == 0x0C) ? 1 : -1];

class DrawDispatcher {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Draw(int first, int second, int third);
};

extern DrawDispatcher *g_DrawDispatcher;

class TextRasterizer {
public:
    u8 DecodeHexDigit(u8 value);
};

class TextRenderer {
public:
    void DrawBox();
    void ConfigureText(float x, float y, bool compact);
};

extern TextRenderer *g_TextRenderer;
extern signed char g_NoticeSelection;
extern float g_ZeroFloat;

class SoundBank {
public:
    void Play(int sound);
};

extern SoundBank *g_SoundBank;

class SpriteGeometry {
public:
    SpriteGeometry *SetFourDwords(u32 first, u32 second, u32 third, u32 fourth);

private:
    u32 first_;
    u32 second_;
    u32 third_;
    u32 fourth_;
};

class FighterState : public Fighter {
public:
    void DrawFacingSprite(short sprite, float position, int first, int second);
    bool IsState50To149();
    void SetNoticeFields(signed char notice, u8 first, u8 second);
    bool IsGroundedStateWindow();
    void ConfigureNoticeText(u8 enabled);
    void BeginNoticeTransition(u8 notice, u8 direction);
    void InitializeNotice(short value);
    void ClearNoticeTransition();
};





extern int g_ClampedGameValue;
void SetClampedGameValue(int value);

#endif
