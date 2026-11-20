#include <windows.h>
#include "Fighter.hpp"
#include "ResultScene.hpp"
class TextureManagerF243 {
    unsigned char allocatedBytes[80];
public:
    TextureManagerF243();
    void AllocateUnformattedSlots(int count);
    void LoadDefault(const char* filename, const char* root);
};
typedef char VerifyTextureSizeF243[(sizeof(TextureManagerF243)==80)?1:-1];
extern const char g_ResultTexturePathAt0065801C[];
extern const char g_ResultTextureRootAt00658014[];
extern Fighter* g_ResultActorPrimaryAt00671418;
extern void* g_ResultActorSecondaryAt0067141C;
extern int g_ResultScoreTotalAt0067160C;
extern int g_ResultTotalDenominatorAt006714BC;
extern short g_ResultBonusAt006714C0;
extern signed char g_ResultSequenceAt00671622;
extern const float g_ResultOneAt0065747C;
extern const float g_ResultHundredAt00657888;
extern const float g_ResultTenThousandAt00658034;
ResultScene::ResultScene()
{
    textures = new TextureManagerF243();
    static_cast<TextureManagerF243*>(textures)->AllocateUnformattedSlots(3);
    static_cast<TextureManagerF243*>(textures)->LoadDefault(g_ResultTexturePathAt0065801C,g_ResultTextureRootAt00658014);
    field014=1.0f;
    field018=0;
    field019=0;
    values[0]=static_cast<Fighter*>(g_ResultActorSecondaryAt0067141C)->field460;
    values[2]=g_ResultScoreTotalAt0067160C;
    field030=static_cast<float>(g_ResultScoreTotalAt0067160C)/static_cast<float>(g_ResultTotalDenominatorAt006714BC)+g_ResultOneAt0065747C;
    values[1]=g_ResultBonusAt006714C0;
    field02C=static_cast<float>(g_ResultBonusAt006714C0)/g_ResultHundredAt00657888+g_ResultOneAt0065747C;
    values[3]=static_cast<int>(g_ResultActorPrimaryAt00671418->health)+(static_cast<int>(g_ResultSequenceAt00671622)-1+static_cast<int>(g_ResultActorPrimaryAt00671418->field39D))*10000;
    field034=static_cast<float>(g_ResultActorPrimaryAt00671418->health)/g_ResultTenThousandAt00658034+static_cast<float>(g_ResultSequenceAt00671622)+static_cast<float>(g_ResultActorPrimaryAt00671418->field39D)-g_ResultOneAt0065747C;
    field038=0;
    field03C=0;
    field040=0;
    offsets[3]=900;
    offsets[2]=900;
    offsets[1]=900;
    offsets[0]=900;
    offsets[4]=1800;
    g_ResultActorPrimaryAt00671418->score+=field038;
    g_ResultActorPrimaryAt00671418->health=10000;
    g_ResultActorPrimaryAt00671418->recoverableHealth=10000;
}
