#ifndef TH075_GAME_LEAF_HELPERS_HPP
#define TH075_GAME_LEAF_HELPERS_HPP

typedef unsigned char u8;
typedef unsigned long u32;

class SpriteGeometry {
public:
    SpriteGeometry *SetFourDwords(u32 first, u32 second, u32 third, u32 fourth);

private:
    u32 first_;
    u32 second_;
    u32 third_;
    u32 fourth_;
};

class AnimationState {
public:
    virtual void OnSecondaryCounterReset();
    void ResetPrimaryCounters(short value);
    void SetThreeCounters(short first, short second, short third);
    void ResetSecondaryCounter(short value);
    void ClearByte40();
};

class BattleEffect {
public:
    void ClearField74();
};

class FighterState {
public:
    void ClearNoticeTransition();
};

class AuxEffect {
public:
    void ClearField8();
};

extern int g_ClampedGameValue;
void SetClampedGameValue(int value);

#endif
