#include "CharacterSelectScene.hpp"
#include "TextureManagerF198.hpp"

CharacterSelectScene::~CharacterSelectScene()
{
    if (menuTextures)
        delete menuTextures;
    if (characterTextures)
        delete characterTextures;
    if (backgroundTextures)
        delete backgroundTextures;
}
