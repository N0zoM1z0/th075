#ifndef TH075_REIMU_ACTION_DISPATCH_HPP
#define TH075_REIMU_ACTION_DISPATCH_HPP

#include "Fighter.hpp"
// Partial interfaces used only through existing receivers. Do not instantiate
// or embed these owners; their complete layouts and original names are unknown.
typedef unsigned char u8;
class ReimuFighter : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
public:
    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF22 - 0xF10];
    short fieldF22;
};

#endif
