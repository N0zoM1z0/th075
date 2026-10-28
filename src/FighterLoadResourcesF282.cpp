#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <new>

// All game owner interfaces below are borrowed from actual calls and native
// object allocation sizes; the complete original FighterState layout is unknown.
class FighterSoundsF282 {public: void Load(const char* filename,const char* archive);};
class FighterTextureF282 {
    unsigned char observedBytes[80];
public:
    FighterTextureF282();
    void AllocateSlots(int count);
    void Load(const char* filename,int pages,const char* root);
    void LoadDefault(const char* filename,const char* root);
};
typedef char VerifyFighterTextureF282[(sizeof(FighterTextureF282)==80)?1:-1];
class FighterCommandsF282 {
    unsigned char observedBytes[24];
public: FighterCommandsF282(FighterTextureF282* texture);
};
typedef char VerifyFighterCommandsF282[(sizeof(FighterCommandsF282)==24)?1:-1];
class FighterScriptsF282 {
public: void LoadFile(const char* filename,int mode,int submode);
        void LoadArchive(const char* filename,const char* root);
};
namespace FighterLogF282 {void __cdecl Append(const char* text);}
extern const char g_LogSoundsAt00658E84[];
extern const char g_SoundFileFormatAt00658E94[];
extern const char g_CharacterMeilingAt00658EA4[];
extern const char g_SoundArchiveMeilingAt00658EAC[];
extern const char g_SoundArchiveDefaultAt00658EB4[];
extern const char g_LogPatternsAt00658EBC[];
extern const char g_LogPicturesAt00658ED0[];
extern const char g_MainTextureFormatAt00658EE4[];
extern const char g_CharacterAliceAt00658EFC[];
extern const char g_CharacterMeiling2At00658F04[];
extern const char g_MainTextureArchiveAltAt00658F0C[];
extern const char g_MainTextureArchiveDefaultAt00658F14[];
extern const char g_SecondaryTextureFormatAt00658F1C[];
extern const char g_CharacterPatchouliAt00658F34[];
extern const char g_CharacterYuyukoAt00658F40[];
extern const char g_CharacterRemiliaAt00658F48[];
extern const char g_CharacterYukariAt00658F50[];
extern const char g_CharacterYoumuAt00658F58[];
extern const char g_CharacterMeiling3At00658F60[];
extern const char g_SecondaryTextureArchiveAltAt00658F68[];
extern const char g_SecondaryTextureArchiveDefaultAt00658F70[];
extern const char g_ScriptFormatAt00658F78[];
extern const char g_ScriptArchiveAt00658F94[];
class FighterLoadF282 {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    void LoadPattern();
    void SetNoticeMode(int value);
    void LoadResources();
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,off) (*reinterpret_cast<type*>(RAW+(off)))
#define NAME (reinterpret_cast<const char*>(RAW+0xc4))
#define CHARACTER (reinterpret_cast<const char*>(RAW+0x1c8))
#define SOUND (reinterpret_cast<FighterSoundsF282*>(RAW+0x6d0))
#define SCRIPT (reinterpret_cast<FighterScriptsF282*>(RAW+0x714))
void FighterLoadF282::LoadResources()
{
    char filename[524];
    FighterLogF282::Append(g_LogSoundsAt00658E84);
    sprintf(filename,g_SoundFileFormatAt00658E94,CHARACTER);
    if (strcmp(NAME,g_CharacterMeilingAt00658EA4)==0)
        SOUND->Load(filename,g_SoundArchiveMeilingAt00658EAC);
    else
        SOUND->Load(filename,g_SoundArchiveDefaultAt00658EB4);
    FighterLogF282::Append(g_LogPatternsAt00658EBC);
    LoadPattern();
    FighterLogF282::Append(g_LogPicturesAt00658ED0);
    FIELD(FighterTextureF282*,4)=new FighterTextureF282();
    FIELD(FighterTextureF282*,0x534)=new FighterTextureF282();
    FIELD(FighterTextureF282*,4)->AllocateSlots(FIELD(short,0x478));
    sprintf(filename,g_MainTextureFormatAt00658EE4,CHARACTER);
    if (strcmp(NAME,g_CharacterAliceAt00658EFC)==0 || strcmp(NAME,g_CharacterMeiling2At00658F04)==0)
        FIELD(FighterTextureF282*,4)->Load(filename,FIELD(signed char,0x2ce)+1,g_MainTextureArchiveAltAt00658F0C);
    else
        FIELD(FighterTextureF282*,4)->Load(filename,FIELD(signed char,0x2ce)+1,g_MainTextureArchiveDefaultAt00658F14);
    FIELD(FighterTextureF282*,0x534)->AllocateSlots(FIELD(signed char,0x532));
    sprintf(filename,g_SecondaryTextureFormatAt00658F1C,CHARACTER);
    if (strcmp(NAME,g_CharacterPatchouliAt00658F34)==0 ||
        strcmp(NAME,g_CharacterYuyukoAt00658F40)==0 ||
        strcmp(NAME,g_CharacterRemiliaAt00658F48)==0 ||
        strcmp(NAME,g_CharacterYukariAt00658F50)==0 ||
        strcmp(NAME,g_CharacterYoumuAt00658F58)==0 ||
        strcmp(NAME,g_CharacterMeiling3At00658F60)==0)
        FIELD(FighterTextureF282*,0x534)->LoadDefault(filename,g_SecondaryTextureArchiveAltAt00658F68);
    else
        FIELD(FighterTextureF282*,0x534)->LoadDefault(filename,g_SecondaryTextureArchiveDefaultAt00658F70);
    sprintf(filename,g_ScriptFormatAt00658F78,NAME,NAME);
    SCRIPT->LoadFile(filename,2,0);
    SCRIPT->LoadArchive(filename,g_ScriptArchiveAt00658F94);
    FIELD(FighterCommandsF282*,0x480)=new FighterCommandsF282(FIELD(FighterTextureF282*,4));
    SetNoticeMode(0);
    Slot6();
}
#undef SCRIPT
#undef SOUND
#undef CHARACTER
#undef NAME
#undef FIELD
#undef RAW
