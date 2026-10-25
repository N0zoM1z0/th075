#ifndef TH075_EFFECT_DISPATCH_F162_HPP
#define TH075_EFFECT_DISPATCH_F162_HPP

// Call-only prefix retaining observed virtual slots; this is not a complete
// effect owner or virtual interface. Never construct or embed these views.
class DispatchingEffectF162 {
public:
    virtual void UnknownSlot0();
    virtual void Advance();
    virtual void DrawPrimary();
    virtual void DrawAlternate();
    virtual void DrawOverlay();
};

class EffectDispatchF162 {
public:
    void DispatchSelected(signed char layer);
    void DispatchAll();
};

#endif
