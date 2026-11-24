#include "BackgroundStageBaseF479.hpp"

// Three separately addressed BG02 stage overrides share the same original
// embedded TextureManager member at BackgroundStage+0x18.
class BackgroundBlendF366 : public NativeBackgroundBaseF479 {
public:
    void ApplyBG02aBlend();
    void ApplyBG02bBlend();
    void ApplyBG02cBlend();
};

extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
extern const float g_BGOffsetXAt00657834;

void BackgroundBlendF366::ApplyBG02aBlend() {
    int x = static_cast<int>(g_CombatViewOffsetX + g_BGOffsetXAt00657834);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.SetBlendMode(0);
}

void BackgroundBlendF366::ApplyBG02bBlend() {
    int x = static_cast<int>(g_CombatViewOffsetX + g_BGOffsetXAt00657834);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.SetBlendMode(0);
}

void BackgroundBlendF366::ApplyBG02cBlend() {
    int x = static_cast<int>(g_CombatViewOffsetX + g_BGOffsetXAt00657834);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.SetBlendMode(0);
}
