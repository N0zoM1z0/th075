#include "TextureManagerF198.hpp"
#include <windows.h>
#include <stdio.h>
#include "ResultListScene.hpp"
#include "PlayerState.hpp"

// ResultListTexture is the shared 80-byte VC7.1 resource manager.
extern const char g_ResultCharacterTexturePatternAt00658080[];
extern const char g_ResultTextureRootAt0065809C[];
extern const char g_CardSpecialAt006580A4[];
extern const char g_CardNormalAt006580AC[];
void ResultListScene::LoadSelectedCharacterResources()
{
    if ((auxiliaryTexture))
        delete (auxiliaryTexture);
    char file[104];
    sprintf(file,g_ResultCharacterTexturePatternAt00658080,static_cast<int>((selectedCharacter)));
    (auxiliaryTexture)=new TextureManagerF198();
    (auxiliaryTexture)->AllocateUnformattedSlots(1);
    (auxiliaryTexture)->LoadDefault(file,g_ResultTextureRootAt0065809C);
    if ((selectedCharacter)==3)
        LoadEncodedCards(g_CharacterNamesAt006714D8[selectedCharacter],g_CardSpecialAt006580A4);
    else
        LoadEncodedCards(g_CharacterNamesAt006714D8[selectedCharacter],g_CardNormalAt006580AC);
}
