#ifndef TH075_MARISA_FIGHTER_HPP
#define TH075_MARISA_FIGHTER_HPP
#include "battle/Fighter.hpp"

// One vertex of Marisa's projectile chain. The reset clears the position
// with integer stores, the renderer reads it as floats.
struct MarisaChainVertex {
    union { float x; unsigned int rawX; };
    union { float y; unsigned int rawY; };
    union { float z; unsigned int rawZ; };
    float alpha;
    unsigned int flags;
    float phase;
    float tail;
};

// Marisa's fighter: vtable Marisa ctor F223 at 0x006592B8.
// Slot overrides use the Fighter slot names; the rest are helpers.
class MarisaFighter : public Fighter {
public:
    MarisaFighter();
    void RenderStage(signed char stage);
    virtual void Advance(); // Slot 1 at 00486550.
    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void PollCommands();
    void AdvanceSequence();
    void RenderChain();
    void CreateOwnedObject(CharacterObject** output);
    void ForwardBaseAction();
    void NoOpSlot18();
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short trackingNodeOrbitAngle;  // +0xF10
    short trackingNodeOrbitPhase;  // +0xF12
    short orbitingNodesRemaining;  // +0xF14
    short trackingNodeDispatchSlot;  // +0xF16
    short trackingNodeLifetimeFrames;  // +0xF18
    short trackingNodeX[6];  // +0xF1A, actions 0x33C-0x341
    short trackingNodeY[6];  // +0xF26, actions 0x33C-0x341
    short longRangeFrames;  // +0xF32
    float stageLayerX[4];  // +0xF34
    unsigned char unknownF44[0xF5C - 0xF44];
    float stageLayerY[4];  // +0xF5C
    unsigned char unknownF6C[0xFFC - 0xF6C];
    unsigned char stageLayerAlpha[4];  // +0xFFC
    unsigned char unknown1000[0x1006 - 0x1000];
    unsigned char chainVisible;  // +0x1006
    unsigned char unknown1007[0x1008 - 0x1007];
    float chainOriginX;  // +0x1008
    float chainOriginY;  // +0x100C
    float chainScale;  // +0x1010
    signed char chainFacing;  // +0x1014
    unsigned char unknown1015[0x1018 - 0x1015];
    MarisaChainVertex chain[74];        // +0x1018 37 segments, two vertices each
};

#endif
