#include <windows.h>
#include "AudioControl.hpp"
#include "SoundBank.hpp"
#include "WindowOverlayF212.hpp"

// The display view carries the observed 120-byte allocation size.
class InputBindingF212 {
public:
    void Configure(void* keymap);
};
extern InputBindingF212 g_InputBindingAAt00671638;
extern InputBindingF212 g_InputBindingBAt00671680;
extern BYTE g_KeymapAAt00671440[];
extern BYTE g_KeymapBAt00671468[];

class WindowDisplayF212 {
    unsigned char nativePhysicalStorage[120];
public:
    WindowDisplayF212();
};
typedef char AssertWindow120F212[(sizeof(WindowDisplayF212)==120)?1:-1];

extern WindowDisplayF212* g_WindowDisplayAt0067143C;
extern WindowOverlayF212* g_WindowOverlayAt006714C4;
extern unsigned char g_SoundVolumeAt006714B6;
extern unsigned char g_StreamVolumeAt006714B7;
extern const char g_WaveArchivePathAt00657A24[];
extern const char g_WaveArchiveIndexAt00657A1C[];

class GameWorkerF212 {
public:
    void Initialize();
};
extern GameWorkerF212 g_WorkerAt006716C8;

namespace GameGlobalsF212 {
void InitializeSound()
{
    g_InputBindingAAt00671638.Configure(g_KeymapAAt00671440);
    g_InputBindingBAt00671680.Configure(g_KeymapBAt00671468);
    g_WindowDisplayAt0067143C = new WindowDisplayF212();
    g_WindowOverlayAt006714C4 = new WindowOverlayF212();
    g_SoundBank = new SoundBank();
    AudioVolume4073B0::SetSoundBankVolume(g_SoundVolumeAt006714B6);
    AudioVolume4073B0::SetStreamVolume(g_StreamVolumeAt006714B7);
    g_SoundBank->LoadArchive(g_WaveArchivePathAt00657A24,
                             g_WaveArchiveIndexAt00657A1C);
    g_WorkerAt006716C8.Initialize();
}
}
