#include "battle/BattleSessionState.hpp"
#include <new>
#include "battle/BattleScene.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "graphics/TextureManagerF198.hpp"


BattleScene::~BattleScene() {
    // Preserve the original literal nonzero second operand and its native test.
    if (g_ReplayModeAt0066C238 == 2 || 4)
        SetClampedGameValue(16);
    if (textures)
        delete static_cast<TextureManagerF198*>(textures);
    if (digitAtlas)
        delete digitAtlas;
    if (comboDisplays[0])
        delete comboDisplays[0];
    if (comboDisplays[1])
        delete comboDisplays[1];
}
