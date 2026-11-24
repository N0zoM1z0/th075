#include "TextureManagerF198.hpp"
#include "DiagnosticLog.hpp"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "Fighter.hpp"
#include "SoundBank.hpp"
#include "ScriptResource4205F0.hpp"

#include "CommandListF283.hpp"

extern const char g_LogSoundsAt00658E84[];
extern const char g_SoundFileFormatAt00658E94[];
extern const char g_CharacterMeilingAt00658EA4[] = "meiling";
extern const char g_SoundArchiveMeilingAt00658EAC[] = "datab";
extern const char g_SoundArchiveDefaultAt00658EB4[] = "data";
extern const char g_LogPatternsAt00658EBC[];
extern const char g_LogPicturesAt00658ED0[];
extern const char g_MainTextureFormatAt00658EE4[];
extern const char g_CharacterAliceAt00658EFC[] = "alice";
extern const char g_CharacterMeiling2At00658F04[] = "meiling";
extern const char g_MainTextureArchiveAltAt00658F0C[] = "datab";
extern const char g_MainTextureArchiveDefaultAt00658F14[] = "data";
extern const char g_SecondaryTextureFormatAt00658F1C[];
extern const char g_CharacterPatchouliAt00658F34[] = "patchouli";
extern const char g_CharacterYuyukoAt00658F40[] = "yuyuko";
extern const char g_CharacterRemiliaAt00658F48[] = "remilia";
extern const char g_CharacterYukariAt00658F50[] = "yukari";
extern const char g_CharacterYoumuAt00658F58[] = "youmu";
extern const char g_CharacterMeiling3At00658F60[] = "meiling";
extern const char g_SecondaryTextureArchiveAltAt00658F68[] = "datab";
extern const char g_SecondaryTextureArchiveDefaultAt00658F70[] = "data";
extern const char g_ScriptFormatAt00658F78[];
extern const char g_ScriptArchiveAt00658F94[] = "datab";
void Fighter::LoadResources()
{
    char filename[524];
    DiagnosticLog::AppendString(g_LogSoundsAt00658E84);
    sprintf(filename,g_SoundFileFormatAt00658E94,tag);
    if (strcmp(name,g_CharacterMeilingAt00658EA4)==0)
        soundBank.LoadArchive(filename,g_SoundArchiveMeilingAt00658EAC);
    else
        soundBank.LoadArchive(filename,g_SoundArchiveDefaultAt00658EB4);
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
    field480=new CommandListF283(static_cast<TextureManagerF198*>(drawing));
    SetNoticeMode(0);
    ResetRound();
}
