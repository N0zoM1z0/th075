#include <windows.h>
#include <stdio.h>

// Physical borrowed texture and card-list interfaces; neither original
// game-scene nor card-list owner is instantiated by this source.
class ResultOldTextureF256 {public: ~ResultOldTextureF256();};
class ResultTextureManagerF256 {
    unsigned char nativeBytes[80];
public:
    ResultTextureManagerF256();
    void AllocateUnformattedSlots(int count);
    void LoadDefault(const char* resource, const char* root);
};
typedef char AssertTexture80F256[(sizeof(ResultTextureManagerF256)==80)?1:-1];
extern const char g_ResultCharacterTexturePatternAt00658080[];
extern const char g_ResultTextureRootAt0065809C[];
extern const char g_CardSpecialAt006580A4[];
extern const char g_CardNormalAt006580AC[];
extern unsigned char g_CharacterCardListsAt006714D8[];
class ResultSceneResourceF256 {
public:
    void LoadSelectedCharacterResources();
    void LoadEncodedCards(void* cardList,const char* name);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,off) (*reinterpret_cast<type*>(RAW+(off)))
void ResultSceneResourceF256::LoadSelectedCharacterResources()
{
    if (FIELD(ResultOldTextureF256*,0x0C))
        delete FIELD(ResultOldTextureF256*,0x0C);
    char file[104];
    sprintf(file,g_ResultCharacterTexturePatternAt00658080,static_cast<int>(FIELD(signed char,0x1C3)));
    FIELD(ResultTextureManagerF256*,0x0C)=new ResultTextureManagerF256();
    FIELD(ResultTextureManagerF256*,0x0C)->AllocateUnformattedSlots(1);
    FIELD(ResultTextureManagerF256*,0x0C)->LoadDefault(file,g_ResultTextureRootAt0065809C);
    if (FIELD(signed char,0x1C3)==3)
        LoadEncodedCards(g_CharacterCardListsAt006714D8 + static_cast<int>(FIELD(signed char,0x1C3))*20,g_CardSpecialAt006580A4);
    else
        LoadEncodedCards(g_CharacterCardListsAt006714D8 + static_cast<int>(FIELD(signed char,0x1C3))*20,g_CardNormalAt006580AC);
}
#undef FIELD
#undef RAW
