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
};

#endif
