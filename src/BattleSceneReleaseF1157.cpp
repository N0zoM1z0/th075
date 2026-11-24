#include <new>
#include "BattleScene.hpp"
#include "GameLeafHelpers.hpp"

class TextureManagerF200 { public: ~TextureManagerF200(); };
extern signed char g_FrameClockModeAt0066C238;

BattleScene::~BattleScene() {
    // Preserve the original literal nonzero second operand and its native test.
    if (g_FrameClockModeAt0066C238 == 2 || 4)
        SetClampedGameValue(16);
    if (textures)
        delete static_cast<TextureManagerF200*>(textures);
    if (digitAtlas)
        delete digitAtlas;
    if (comboDisplays[0])
        delete comboDisplays[0];
    if (comboDisplays[1])
        delete comboDisplays[1];
}
