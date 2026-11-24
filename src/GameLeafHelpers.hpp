#ifndef TH075_GAME_LEAF_HELPERS_HPP
#define TH075_GAME_LEAF_HELPERS_HPP
#include "FloatConstants.hpp"
#include "GameSharedState.hpp"

#include "Fighter.hpp"
#include "SoundBank.hpp"
typedef unsigned char u8;
typedef unsigned long u32;

class SpriteQuad40CA80;

class SpriteScene {
public:
    static void DispatchGlobalDraw(SpriteQuad40CA80* destination, unsigned long* color, SpriteQuad40CA80* source);
};

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





void SetClampedGameValue(int value);

#endif
