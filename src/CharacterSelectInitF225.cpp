#include <windows.h>
// Borrowed physical interfaces and three 80-byte allocation carriers. The
// surrounding scene and actor layouts remain unknown; this source never
// instantiates an incomplete scene/actor owner.
class SceneBaseF225 {
public:
    SceneBaseF225();
    virtual ~SceneBaseF225();
};
class ActorResourceF225 {
public:
    virtual void Reserved0();
    virtual void Reserved1();
    virtual void Reserved2();
    virtual void Reserved3();
    virtual void Reserved4();
    virtual ~ActorResourceF225(); // Native deleting destructor in slot five.
};
class TextureAllocF225 {
    unsigned char observedBytes[80];
public:
    TextureAllocF225();
    void AllocateUnformattedSlots(int count);
    void LoadDefault(const char* filename, const char* root);
};
typedef char VerifyTexture80F225[(sizeof(TextureAllocF225)==80)?1:-1];
extern ActorResourceF225* g_ActorAAt00671418;
extern ActorResourceF225* g_ActorBAt0067141C;
extern const char g_SelectTextureDataAt006581EC[];
extern const char g_SelectTextureRootAt006581E4[];
extern const char g_CharacterTextureDataAt0065820C[];
extern const char g_CharacterTextureRootAt00658204[];
extern const char g_BackgroundTextureDataAt00658230[];
extern const char g_BackgroundTextureRootAt00658228[];
extern unsigned char g_SelectionModeAt0066C238;
extern unsigned char g_FramePadAt00671620;
extern unsigned char g_ContinueUsedAt00671624;
namespace GameSettingsF225 {
    void Load();
    unsigned char ReadDefault(unsigned char index);
    unsigned char ReadControls(unsigned char index, unsigned char player);
}
class CharacterSelectCtorF225 : public SceneBaseF225 {
public:
    CharacterSelectCtorF225();
    virtual ~CharacterSelectCtorF225();
    void ResetSelection();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
CharacterSelectCtorF225::CharacterSelectCtorF225()
{
    if (g_ActorAAt00671418) {
        delete g_ActorAAt00671418;
        g_ActorAAt00671418=0;
    }
    if (g_ActorBAt0067141C) {
        delete g_ActorBAt0067141C;
        g_ActorBAt0067141C=0;
    }
    FIELD(TextureAllocF225*,0x08)=new TextureAllocF225();
    FIELD(TextureAllocF225*,0x08)->AllocateUnformattedSlots(8);
    FIELD(TextureAllocF225*,0x08)->LoadDefault(g_SelectTextureDataAt006581EC,g_SelectTextureRootAt006581E4);
    FIELD(TextureAllocF225*,0x44)=new TextureAllocF225();
    FIELD(TextureAllocF225*,0x44)->AllocateUnformattedSlots(22);
    FIELD(TextureAllocF225*,0x44)->LoadDefault(g_CharacterTextureDataAt0065820C,g_CharacterTextureRootAt00658204);
    FIELD(TextureAllocF225*,0x48)=new TextureAllocF225();
    FIELD(TextureAllocF225*,0x48)->AllocateUnformattedSlots(17);
    FIELD(TextureAllocF225*,0x48)->LoadDefault(g_BackgroundTextureDataAt00658230,g_BackgroundTextureRootAt00658228);
    g_SelectionModeAt0066C238=1;
    g_FramePadAt00671620=0;
    g_ContinueUsedAt00671624=0;
    GameSettingsF225::Load();
    int i;
    for (i=0;i<30;++i)
        reinterpret_cast<unsigned char*>(this)[0x78+i] = GameSettingsF225::ReadDefault(static_cast<unsigned char>(i));
    for (i=0;i<15;++i) {
        reinterpret_cast<unsigned char*>(this)[0x50+i] = GameSettingsF225::ReadControls(static_cast<unsigned char>(i),0);
        reinterpret_cast<unsigned char*>(this)[0x64+i] = GameSettingsF225::ReadControls(static_cast<unsigned char>(i),1);
    }
    FIELD(unsigned char,0xf2)=0;
    FIELD(unsigned char,0xf3)=0;
    ResetSelection();
}
#undef FIELD
