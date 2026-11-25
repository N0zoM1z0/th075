#include "ui/CharacterSelectScene.hpp"
#include "graphics/TextureManagerF198.hpp"

CharacterSelectScene::~CharacterSelectScene()
{
    if (menuTextures)
        delete menuTextures;
    if (characterTextures)
        delete characterTextures;
    if (backgroundTextures)
        delete backgroundTextures;
}
