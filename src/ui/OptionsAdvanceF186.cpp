#include "engine/SceneTransition.hpp"
#include "config/GameConfigStorage.hpp"
#include "engine/GameSharedState.hpp"
#include "audio/AudioControl.hpp"
#include "ui/OptionsScene.hpp"
#include "ui/MenuInputF184.hpp"
#include "engine/GameLeafHelpers.hpp"

// Borrowed call-only views of external scene effects. Complete layouts unknown.
namespace Graphics { void Present(); }
namespace AudioVolume4073B0 {
    void __cdecl SetSoundBankVolume(signed char);
    void __cdecl SetStreamVolume(signed char);
}
namespace OptionsSettingsF186 { void SaveConfiguration(); }

extern unsigned char g_OptionsFlagAt00671604;
extern unsigned char g_OptionsFlagAt00671430;
extern unsigned char g_OptionsFlagAt00671428;

#define SOUND(value) g_SoundBank->Play(value)

unsigned short OptionsScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if (verticalInput < 0) {
        SOUND(39);
        currentItem--;
        if (currentItem < 0)
            currentItem = 6;
        Apply(static_cast<unsigned char>(currentItem));
    }
    if (verticalInput > 0) {
        SOUND(39);
        currentItem++;
        if (currentItem > 6)
            currentItem = 0;
        Apply(static_cast<unsigned char>(currentItem));
    }

    switch (currentItem) {
    case 0:
        if (horizontalInput || confirmInput) {
            SOUND(39);
            g_OptionsModeAt006714D0 = static_cast<signed char>(
                (g_OptionsModeAt006714D0 + horizontalInput +
                confirmInput + 4) % 4);
        }
        break;
    case 1:
        if (horizontalInput || confirmInput) {
            SOUND(45);
            g_OptionsFlagAt00671604 = g_OptionsFlagAt00671604 ? 0 : 1;
        }
        break;
    case 2:
        if (horizontalInput || confirmInput) {
            SOUND(45);
            g_OptionsFlagAt00671430 = g_OptionsFlagAt00671430 ? 0 : 1;
        }
        break;
    case 3:
        if (horizontalInput || confirmInput) {
            SOUND(45);
            g_OptionsFlagAt00671428 = g_OptionsFlagAt00671428 ? 0 : 1;
        }
        break;
    case 4:
        if (horizontalInput > 0) {
            reinterpret_cast<signed char&>(g_StreamVolumeAt006714B7) += 5;
            if (static_cast<signed char>(g_StreamVolumeAt006714B7) > 100) g_StreamVolumeAt006714B7 = 100;
            AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
            AudioControl407CA0::ApplyVolumeOffset(0);
        }
        if (horizontalInput < 0) {
            reinterpret_cast<signed char&>(g_StreamVolumeAt006714B7) -= 5;
            if (static_cast<signed char>(g_StreamVolumeAt006714B7) < 0) g_StreamVolumeAt006714B7 = 0;
            AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
            AudioControl407CA0::ApplyVolumeOffset(0);
        }
        if (confirmInput)
            SOUND(45);
        break;
    case 5:
        if (pressedItem == 0) {
            SOUND(40);
            pressedItem = 60;
        }
        pressedItem--;
        if (horizontalInput > 0) {
            reinterpret_cast<signed char&>(g_SoundVolumeAt006714B6) += 5;
            if (static_cast<signed char>(g_SoundVolumeAt006714B6) > 100) g_SoundVolumeAt006714B6 = 100;
            AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
        }
        if (horizontalInput < 0) {
            reinterpret_cast<signed char&>(g_SoundVolumeAt006714B6) -= 5;
            if (static_cast<signed char>(g_SoundVolumeAt006714B6) < 0) g_SoundVolumeAt006714B6 = 0;
            AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
        }
        if (confirmInput)
            SOUND(45);
        break;
    case 6:
        if (confirmInput) {
            SOUND(45);
            OptionsSettingsF186::SaveConfiguration();
            return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
        }
        break;
    }

    if (displayAlpha < 255)
        displayAlpha += 25;
    if (cancelInput == 1) {
        SOUND(40);
        OptionsSettingsF186::SaveConfiguration();
        return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
    }
    return 9;
}

#undef SOUND
