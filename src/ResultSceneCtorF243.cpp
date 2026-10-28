#include <windows.h>
// Borrowed native base/texture constructor calls. The full original result
// scene and actor type layouts are not inferred from this partial caller.
class SceneBaseF243 {
public:
    SceneBaseF243();
    virtual ~SceneBaseF243();
};
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
extern void* g_ResultActorPrimaryAt00671418;
extern void* g_ResultActorSecondaryAt0067141C;
extern int g_ResultScoreTotalAt0067160C;
extern int g_ResultTotalDenominatorAt006714BC;
extern short g_ResultBonusAt006714C0;
extern signed char g_ResultSequenceAt00671622;
extern const float g_ResultOneAt0065747C;
extern const float g_ResultHundredAt00657888;
extern const float g_ResultTenThousandAt00658034;
class ResultSceneCtorF243 : public SceneBaseF243 {
public:
    ResultSceneCtorF243();
    virtual ~ResultSceneCtorF243();
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,off) (*reinterpret_cast<type*>(RAW+(off)))
#define ACTOR(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(g_ResultActorPrimaryAt00671418)+(off)))
ResultSceneCtorF243::ResultSceneCtorF243()
{
    FIELD(TextureManagerF243*,0x08) = new TextureManagerF243();
    FIELD(TextureManagerF243*,0x08)->AllocateUnformattedSlots(3);
    FIELD(TextureManagerF243*,0x08)->LoadDefault(g_ResultTexturePathAt0065801C,g_ResultTextureRootAt00658014);
    FIELD(float,0x14)=1.0f;
    FIELD(unsigned char,0x18)=0;
    FIELD(unsigned char,0x19)=0;
    FIELD(int,0x1c)=*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(g_ResultActorSecondaryAt0067141C)+0x460);
    FIELD(int,0x24)=g_ResultScoreTotalAt0067160C;
    FIELD(float,0x30)=static_cast<float>(g_ResultScoreTotalAt0067160C)/static_cast<float>(g_ResultTotalDenominatorAt006714BC)+g_ResultOneAt0065747C;
    FIELD(int,0x20)=g_ResultBonusAt006714C0;
    FIELD(float,0x2c)=static_cast<float>(g_ResultBonusAt006714C0)/g_ResultHundredAt00657888+g_ResultOneAt0065747C;
    FIELD(int,0x28)=static_cast<int>(ACTOR(short,0x324))+(static_cast<int>(g_ResultSequenceAt00671622)-1+static_cast<int>(ACTOR(signed char,0x39d)))*10000;
    FIELD(float,0x34)=static_cast<float>(ACTOR(short,0x324))/g_ResultTenThousandAt00658034+static_cast<float>(g_ResultSequenceAt00671622)+static_cast<float>(ACTOR(signed char,0x39d))-g_ResultOneAt0065747C;
    FIELD(int,0x38)=0;
    FIELD(int,0x3c)=0;
    FIELD(unsigned char,0x40)=0;
    FIELD(short,0x48)=900;
    FIELD(short,0x46)=900;
    FIELD(short,0x44)=900;
    FIELD(short,0x42)=900;
    FIELD(short,0x4a)=1800;
    ACTOR(int,0x2d0)+=FIELD(int,0x38);
    ACTOR(short,0x324)=10000;
    ACTOR(short,0x326)=10000;
}
#undef ACTOR
#undef FIELD
#undef RAW
