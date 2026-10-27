#include "OptionsAdvanceF186.hpp"
#include "MenuInputF184.hpp"
#include "GameLeafHelpers.hpp"

// Borrowed call-only views of external scene effects. Complete layouts unknown.
class OptionsDrawF186 {
public:
    virtual void Unknown0();
    virtual void Unknown1();
    virtual void RenderOptions();
};
class OptionsSelectF186 {
public:
    void Apply(unsigned char option);
};
namespace Graphics { void Present(); }
namespace AudioVolume4073B0 {
    void __cdecl SetSoundBankVolume(signed char);
    void __cdecl SetStreamVolume(signed char);
}
namespace AudioControl407CA0 { void __cdecl ApplyVolumeOffset(long); }
namespace OptionsSettingsF186 { void SaveConfiguration(); }

extern signed char g_OptionsModeAt006714D0;
extern unsigned char g_OptionsFlagAt00671604;
extern unsigned char g_OptionsFlagAt00671430;
extern unsigned char g_OptionsFlagAt00671428;
extern signed char g_StreamVolumeAt006714B7;
extern signed char g_SoundVolumeAt006714B6;

#define FIELD(type, off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (off)))
#define SOUND(value) g_SoundBank->Play(value)

unsigned short OptionsAdvanceF186::Advance()
{
    reinterpret_cast<ReplayMenuInputF184*>(this)->PollInput();
    reinterpret_cast<OptionsDrawF186*>(this)->RenderOptions();
    Graphics::Present();
    if (FIELD(signed char, 0x16) < 0) {
        SOUND(39);
        FIELD(short, 0x10)--;
        if (FIELD(short, 0x10) < 0)
            FIELD(short, 0x10) = 6;
        reinterpret_cast<OptionsSelectF186*>(this)->Apply(static_cast<unsigned char>(FIELD(short, 0x10)));
    }
    if (FIELD(signed char, 0x16) > 0) {
        SOUND(39);
        FIELD(short, 0x10)++;
        if (FIELD(short, 0x10) > 6)
            FIELD(short, 0x10) = 0;
        reinterpret_cast<OptionsSelectF186*>(this)->Apply(static_cast<unsigned char>(FIELD(short, 0x10)));
    }

    switch (FIELD(short, 0x10)) {
    case 0:
        if (FIELD(signed char, 0x15) || FIELD(signed char, 0x17)) {
            SOUND(39);
            g_OptionsModeAt006714D0 = static_cast<signed char>(
                (g_OptionsModeAt006714D0 + FIELD(signed char, 0x15) +
                FIELD(signed char, 0x17) + 4) % 4);
        }
        break;
    case 1:
        if (FIELD(signed char, 0x15) || FIELD(signed char, 0x17)) {
            SOUND(45);
            g_OptionsFlagAt00671604 = g_OptionsFlagAt00671604 ? 0 : 1;
        }
        break;
    case 2:
        if (FIELD(signed char, 0x15) || FIELD(signed char, 0x17)) {
            SOUND(45);
            g_OptionsFlagAt00671430 = g_OptionsFlagAt00671430 ? 0 : 1;
        }
        break;
    case 3:
        if (FIELD(signed char, 0x15) || FIELD(signed char, 0x17)) {
            SOUND(45);
            g_OptionsFlagAt00671428 = g_OptionsFlagAt00671428 ? 0 : 1;
        }
        break;
    case 4:
        if (FIELD(signed char, 0x15) > 0) {
            g_StreamVolumeAt006714B7 += 5;
            if (g_StreamVolumeAt006714B7 > 100) g_StreamVolumeAt006714B7 = 100;
            AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
            AudioControl407CA0::ApplyVolumeOffset(0);
        }
        if (FIELD(signed char, 0x15) < 0) {
            g_StreamVolumeAt006714B7 -= 5;
            if (g_StreamVolumeAt006714B7 < 0) g_StreamVolumeAt006714B7 = 0;
            AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
            AudioControl407CA0::ApplyVolumeOffset(0);
        }
        if (FIELD(signed char, 0x17))
            SOUND(45);
        break;
    case 5:
        if (FIELD(short, 0x12) == 0) {
            SOUND(40);
            FIELD(short, 0x12) = 60;
        }
        FIELD(short, 0x12)--;
        if (FIELD(signed char, 0x15) > 0) {
            g_SoundVolumeAt006714B6 += 5;
            if (g_SoundVolumeAt006714B6 > 100) g_SoundVolumeAt006714B6 = 100;
            AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
        }
        if (FIELD(signed char, 0x15) < 0) {
            g_SoundVolumeAt006714B6 -= 5;
            if (g_SoundVolumeAt006714B6 < 0) g_SoundVolumeAt006714B6 = 0;
            AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
        }
        if (FIELD(signed char, 0x17))
            SOUND(45);
        break;
    case 6:
        if (FIELD(signed char, 0x17)) {
            SOUND(45);
            OptionsSettingsF186::SaveConfiguration();
            return 0x2202;
        }
        break;
    }

    if (FIELD(unsigned char, 0x14) < 255)
        FIELD(unsigned char, 0x14) += 25;
    if (FIELD(signed char, 0x18) == 1) {
        SOUND(40);
        OptionsSettingsF186::SaveConfiguration();
        return 0x2202;
    }
    return 9;
}

#undef FIELD
#undef SOUND
