#ifndef TH075_BATTLE_ANIMATION_BINDING_F139_HPP
#define TH075_BATTLE_ANIMATION_BINDING_F139_HPP

// Pointer-only views. The complete game owners, original class identities
// and frame record layouts remain unknown; never construct or embed them.
class AnimationFrameF139;

class AnimationRowF139 {
public:
    AnimationFrameF139& at(unsigned int index);
    unsigned int size() const;
};

class AnimationRowsF139 {
public:
    AnimationRowF139*& at(unsigned int index);
};

class BattleAnimationBindingF139 {
public:
    // Actual callback slot 0; only this observed prefix is described.
    virtual void BindAnimation();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x008 - 0x004];
    AnimationFrameF139* field008;
    unsigned char unknown00C[0x060 - 0x00C];
    short field060;
    short field062;
    unsigned char unknown064[0x074 - 0x064];
    AnimationFrameF139* field074;
    unsigned char unknown078[0x0C4 - 0x078];
    AnimationRowsF139* field0C4;
};

#endif
