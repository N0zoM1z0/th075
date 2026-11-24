#include "TextureManagerF198.hpp"
#include "DiagnosticLog.hpp"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "Fighter.hpp"
#include "SoundBank.hpp"
#include "ScriptResource4205F0.hpp"

// The command container has its own observed 24-byte allocation.
class FighterCommandsF282 {
    unsigned char observedBytes[24];
public: FighterCommandsF282(FighterTextureF282* texture);
};
typedef char VerifyFighterCommandsF282[(sizeof(FighterCommandsF282)==24)?1:-1];
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
void Fighter::LoadResources()
{
    char filename[524];
    DiagnosticLog::AppendString(g_LogSoundsAt00658E84);
    sprintf(filename,g_SoundFileFormatAt00658E94,tag);
    if (strcmp(name,g_CharacterMeilingAt00658EA4)==0)
        reinterpret_cast<SoundBank*>(&soundResources)->LoadArchive(filename,g_SoundArchiveMeilingAt00658EAC);
    else
        reinterpret_cast<SoundBank*>(&soundResources)->LoadArchive(filename,g_SoundArchiveDefaultAt00658EB4);
    DiagnosticLog::AppendString(g_LogPatternsAt00658EBC);
    LoadPattern();
    DiagnosticLog::AppendString(g_LogPicturesAt00658ED0);
    drawing=new TextureManagerF198();
    field534Texture=reinterpret_cast<FighterTextureF282*>(new TextureManagerF198());
    static_cast<TextureManagerF198*>(drawing)->AllocateUnformattedSlots(field478);
    sprintf(filename,g_MainTextureFormatAt00658EE4,tag);
    if (strcmp(name,g_CharacterAliceAt00658EFC)==0 || strcmp(name,g_CharacterMeiling2At00658F04)==0)
        static_cast<TextureManagerF198*>(drawing)->Load(filename,static_cast<signed char>(field2CE+1),g_MainTextureArchiveAltAt00658F0C);
    else
        static_cast<TextureManagerF198*>(drawing)->Load(filename,static_cast<signed char>(field2CE+1),g_MainTextureArchiveDefaultAt00658F14);
    reinterpret_cast<TextureManagerF198*>(field534Texture)->AllocateUnformattedSlots(field532);
    sprintf(filename,g_SecondaryTextureFormatAt00658F1C,tag);
    if (strcmp(name,g_CharacterPatchouliAt00658F34)==0 ||
        strcmp(name,g_CharacterYuyukoAt00658F40)==0 ||
        strcmp(name,g_CharacterRemiliaAt00658F48)==0 ||
        strcmp(name,g_CharacterYukariAt00658F50)==0 ||
        strcmp(name,g_CharacterYoumuAt00658F58)==0 ||
        strcmp(name,g_CharacterMeiling3At00658F60)==0)
        reinterpret_cast<TextureManagerF198*>(field534Texture)->LoadDefault(filename,g_SecondaryTextureArchiveAltAt00658F68);
    else
        reinterpret_cast<TextureManagerF198*>(field534Texture)->LoadDefault(filename,g_SecondaryTextureArchiveDefaultAt00658F70);
    sprintf(filename,g_ScriptFormatAt00658F78,name,name);
    script.LoadFile(filename,2,0);
    script.LoadArchive(filename,g_ScriptArchiveAt00658F94);
    field480=new FighterCommandsF282(static_cast<FighterTextureF282*>(drawing));
    SetNoticeMode(0);
    ResetRound();
}
