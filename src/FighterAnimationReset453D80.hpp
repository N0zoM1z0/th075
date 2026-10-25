#pragma once

class AnimationFrameF156;

// Declaration-only container interfaces, observed through real thiscall sites.
// Their original element/owner types and complete layouts remain unknown.
// Never construct or embed any of these receiver views.
class AnimationSequenceF156 {
public:
    AnimationFrameF156& At(unsigned int index);
    unsigned int Count() const;
};

class AnimationSequencesF156 {
public:
    AnimationSequenceF156*& At(unsigned int index);
};

class FighterAnimationReset453D80 {
public:
    virtual void BindAnimation(); // Observed slot0; no full vtable claim.
};
