#ifndef TH075_REIMU_ACTION_DISPATCH_HPP
#define TH075_REIMU_ACTION_DISPATCH_HPP

// Partial interfaces used only through existing receivers. Do not instantiate
// or embed these owners; their complete layouts and original names are unknown.
typedef unsigned char u8;
class ActionSequenceSlots {
public:
    void *&At(unsigned int index);
};
class ReimuFighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
