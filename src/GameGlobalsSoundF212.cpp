#include <windows.h>

// Call-only views of the original game-level sound initialization.
// Allocation sizes 120, 8, 20 are native-observed operator new arguments;
// physical allocation carriers are not assertions of full original types.
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
class WindowOverlayF212 {
    unsigned char nativePhysicalStorage[8];
public:
    WindowOverlayF212();
};
class AudioDeviceF212 {
    unsigned char nativePhysicalStorage[20];
public:
    AudioDeviceF212();
    void LoadWaveBank(const char*, const char*);
};
typedef char AssertWindow120F212[(sizeof(WindowDisplayF212)==120)?1:-1];
typedef char AssertOverlay8F212[(sizeof(WindowOverlayF212)==8)?1:-1];
typedef char AssertAudio20F212[(sizeof(AudioDeviceF212)==20)?1:-1];

extern WindowDisplayF212* g_WindowDisplayAt0067143C;
extern WindowOverlayF212* g_WindowOverlayAt006714C4;
extern AudioDeviceF212* g_AudioDeviceAt00671618;
extern unsigned char g_SoundVolumeAt006714B6;
extern unsigned char g_StreamVolumeAt006714B7;
extern const char g_WaveArchivePathAt00657A24[];
extern const char g_WaveArchiveIndexAt00657A1C[];

class GameWorkerF212 {
public:
    void Initialize();
};
extern GameWorkerF212 g_WorkerAt006716C8;
namespace AudioVolumeF212 {
    void SetSoundBankVolume(unsigned char volume);
    void SetStreamVolume(unsigned char volume);
}

namespace GameGlobalsF212 {
void InitializeSound()
{
    g_InputBindingAAt00671638.Configure(g_KeymapAAt00671440);
    g_InputBindingBAt00671680.Configure(g_KeymapBAt00671468);
    g_WindowDisplayAt0067143C = new WindowDisplayF212();
    g_WindowOverlayAt006714C4 = new WindowOverlayF212();
    g_AudioDeviceAt00671618 = new AudioDeviceF212();
    AudioVolumeF212::SetSoundBankVolume(g_SoundVolumeAt006714B6);
    AudioVolumeF212::SetStreamVolume(g_StreamVolumeAt006714B7);
    g_AudioDeviceAt00671618->LoadWaveBank(g_WaveArchivePathAt00657A24,
                                          g_WaveArchiveIndexAt00657A1C);
    g_WorkerAt006716C8.Initialize();
}
}
