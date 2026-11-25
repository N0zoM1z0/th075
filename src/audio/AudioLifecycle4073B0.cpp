#include "audio/AudioStream.hpp"
#include "audio/AudioControl.hpp"
#include "audio/SoundBank.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

signed char soundBankVolume = 100;
signed char masterVolume = 100;
SoundBank* g_SoundBank;
namespace AudioVolume4073B0 {
void __cdecl SetSoundBankVolume(signed char volume) {
    soundBankVolume = volume;
}
void __cdecl SetStreamVolume(signed char volume) {
    masterVolume = volume;
}
}

void SoundBank::Play(int index) {
    if (index < 0 || index >= static_cast<int>(buffers.size()))
        return;
    if (buffers[index] == 0)
        return;
    IDirectSoundBuffer8* buffer = buffers.at(index);
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
