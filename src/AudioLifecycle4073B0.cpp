#include "AudioStream.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

extern signed char soundBankVolume;
extern signed char masterVolume;
namespace AudioVolume4073B0 {
void __cdecl SetSoundBankVolume(signed char volume) {
    soundBankVolume = volume;
}
void __cdecl SetStreamVolume(signed char volume) {
    masterVolume = volume;
}
}

// Separate pointer-only interfaces preserve accepted source declarations.
// Neither owner has a complete layout here; never instantiate or embed it.
class SoundBankPlay4079C0 {
public:
    void Play(int);
    unsigned int Size();
    IDirectSoundBuffer8*& Unchecked(unsigned int);
    IDirectSoundBuffer8*& At(unsigned int);
};
void SoundBankPlay4079C0::Play(int index) {
    if (index < 0 || index >= static_cast<int>(Size()))
        return;
    if (Unchecked(index) == 0)
        return;
    IDirectSoundBuffer8* buffer = At(index);
    buffer->Stop();
    buffer->SetCurrentPosition(0);
    buffer->SetVolume((soundBankVolume - 100) * 50);
    buffer->Play(0, 0, 0);
}

AudioStream::AudioStream() {
    buffer = 0;
    loopEnd = 0;
    loopLength = 0;
    loopEnabled = 0;
    volume = 0;
    file = 0;
    bufferBytes = 0;
}
AudioStream::~AudioStream() {
    if (!archiveMode && file) {
        CloseHandle(file);
        file = 0;
    }
    if (buffer) {
        buffer->Release();
        buffer = 0;
    }
}
