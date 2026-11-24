#include "GeometryConstants.hpp"
#include "BackgroundStages.hpp"

extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;

void BackgroundBG02aF377::Slot2() {
    int x = static_cast<int>(g_CombatViewOffsetX + GeometryConstants::HundredSixty);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.SetBlendMode(0);
}

void BackgroundBG02bF377::Slot2() {
    int x = static_cast<int>(g_CombatViewOffsetX + GeometryConstants::HundredSixty);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.SetBlendMode(0);
}

void BackgroundBG02cF377::Slot2() {
    int x = static_cast<int>(g_CombatViewOffsetX + GeometryConstants::HundredSixty);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.SetBlendMode(0);
}
