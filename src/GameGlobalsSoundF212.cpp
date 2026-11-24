#include "GameConfigStorage.hpp"
#include "TextOverlay.hpp"
#include "SelectionInput4388D0.hpp"
#include <windows.h>
#include "AudioControl.hpp"
#include "SoundBank.hpp"
#include "WindowOverlayF212.hpp"
#include "CombatEffects.hpp"


extern const char g_WaveArchivePathAt00657A24[];
extern const char g_WaveArchiveIndexAt00657A1C[];


namespace GameGlobalsF212 {
void InitializeSound()
{
    g_InputMappings[0].SetBindings(g_KeyBindingsAt00671440);
    g_InputMappings[1].SetBindings(g_KeyBindingsAt00671440 + sizeof(InputBindingKeys));
    g_TextRenderer = new TextOverlay();
    g_WindowOverlayAt006714C4 = new WindowOverlayF212();
    g_SoundBank = new SoundBank();
    AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
    AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
    g_SoundBank->LoadArchive(g_WaveArchivePathAt00657A24,
                             g_WaveArchiveIndexAt00657A1C);
    g_CombatEffects.LoadResources();
}
}
