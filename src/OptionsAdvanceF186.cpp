#include "AudioControl.hpp"
#include "OptionsScene.hpp"
#include "MenuInputF184.hpp"
#include "GameLeafHelpers.hpp"

// Borrowed call-only views of external scene effects. Complete layouts unknown.
namespace Graphics { void Present(); }
namespace AudioVolume4073B0 {
    void __cdecl SetSoundBankVolume(signed char);
    void __cdecl SetStreamVolume(signed char);
}
namespace OptionsSettingsF186 { void SaveConfiguration(); }

extern signed char g_OptionsModeAt006714D0;
extern unsigned char g_OptionsFlagAt00671604;
extern unsigned char g_OptionsFlagAt00671430;
extern unsigned char g_OptionsFlagAt00671428;
extern unsigned char g_StreamVolumeAt006714B7;
extern unsigned char g_SoundVolumeAt006714B6;

#define SOUND(value) g_SoundBank->Play(value)

unsigned short OptionsScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if (field016 < 0) {
        SOUND(39);
        currentItem--;
        if (currentItem < 0)
            currentItem = 6;
        Apply(static_cast<unsigned char>(currentItem));
    }
    if (field016 > 0) {
        SOUND(39);
        currentItem++;
        if (currentItem > 6)
            currentItem = 0;
        Apply(static_cast<unsigned char>(currentItem));
    }

    switch (currentItem) {
    case 0:
        if (field015 || field017) {
            SOUND(39);
            g_OptionsModeAt006714D0 = static_cast<signed char>(
                (g_OptionsModeAt006714D0 + field015 +
                field017 + 4) % 4);
        }
        break;
    case 1:
        if (field015 || field017) {
            SOUND(45);
            g_OptionsFlagAt00671604 = g_OptionsFlagAt00671604 ? 0 : 1;
        }
        break;
    case 2:
        if (field015 || field017) {
            SOUND(45);
            g_OptionsFlagAt00671430 = g_OptionsFlagAt00671430 ? 0 : 1;
        }
        break;
    case 3:
        if (field015 || field017) {
            SOUND(45);
            g_OptionsFlagAt00671428 = g_OptionsFlagAt00671428 ? 0 : 1;
        }
        break;
    case 4:
        if (field015 > 0) {
            reinterpret_cast<signed char&>(g_StreamVolumeAt006714B7) += 5;
            if (static_cast<signed char>(g_StreamVolumeAt006714B7) > 100) g_StreamVolumeAt006714B7 = 100;
            AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
            AudioControl407CA0::ApplyVolumeOffset(0);
        }
        if (field015 < 0) {
            reinterpret_cast<signed char&>(g_StreamVolumeAt006714B7) -= 5;
            if (static_cast<signed char>(g_StreamVolumeAt006714B7) < 0) g_StreamVolumeAt006714B7 = 0;
            AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
            AudioControl407CA0::ApplyVolumeOffset(0);
        }
        if (field017)
            SOUND(45);
        break;
    case 5:
        if (pressedItem == 0) {
            SOUND(40);
            pressedItem = 60;
        }
        pressedItem--;
        if (field015 > 0) {
            reinterpret_cast<signed char&>(g_SoundVolumeAt006714B6) += 5;
            if (static_cast<signed char>(g_SoundVolumeAt006714B6) > 100) g_SoundVolumeAt006714B6 = 100;
            AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
        }
        if (field015 < 0) {
            reinterpret_cast<signed char&>(g_SoundVolumeAt006714B6) -= 5;
            if (static_cast<signed char>(g_SoundVolumeAt006714B6) < 0) g_SoundVolumeAt006714B6 = 0;
            AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
        }
        if (field017)
            SOUND(45);
        break;
    case 6:
        if (field017) {
            SOUND(45);
            OptionsSettingsF186::SaveConfiguration();
            return 0x2202;
        }
        break;
    }

    if (field014 < 255)
        field014 += 25;
    if (field018 == 1) {
        SOUND(40);
        OptionsSettingsF186::SaveConfiguration();
        return 0x2202;
    }
    return 9;
}

#undef SOUND
